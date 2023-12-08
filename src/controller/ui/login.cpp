#include "login.h"
#include "repository.h"
#include "user_helper.h"

#include <QDesktopServices>
#include <QHttpServerResponse>
#include <QString>

static const auto AUTH_SERVER_URL = QStringLiteral("https://link.sast.fun/auth");
static const auto AUTH_CLIENT_ID = QStringLiteral("381c34b9-14a4-4df9-a9db-40c2455be09f");
static const auto OK_RESPONSE = QByteArrayLiteral(R"(
                <!DOCTYPE html>
                <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>Login Success</title>
                    <style>
                        body {
                            font-family: Arial, sans-serif;
                            background-color: #f0f0f0;
                            text-align: center;
                            padding: 50px;
                        }
                        .message {
                            background-color: #4CAF50;
                            color: white;
                            padding: 20px;
                            border-radius: 5px;
                            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
                        }
                    </style>
                </head>
                <body>
                    <div class="message" id="successMessage">
                        <p id="messageText">SAST Link Authorization Successful, please close this page</p>
                    </div>
                    <script>
                        var userLanguage = navigator.language || navigator.userLanguage;
                        var messages = {
                            'zh-CN': 'SAST Link授权成功，请关闭当前网页',
                            'en': 'SAST Link Authorization Successful, please close this page'
                        };
                        var messageText = document.getElementById('messageText');
                        if (messages[userLanguage]) {
                            messageText.textContent = messages[userLanguage];
                        }
                        window.close();
                    </script>
                </body>
                </html>
                )");
static const auto ERROR_RESPONSE = QStringLiteral(R"(
                <!DOCTYPE html>
                <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>Authorization Failed</title>
                    <style>
                        body {
                            font-family: Arial, sans-serif;
                            background-color: #f0f0f0;
                            text-align: center;
                            padding: 50px;
                        }
                        .message {
                            background-color: #FF5733;
                            color: white;
                            padding: 20px;
                            border-radius: 5px;
                            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
                        }
                    </style>
                </head>
                <body>
                    <div class="message" id="failureMessage">
                        <p id="messageText">Authorization Failed, error: %1</p>
                    </div>
                    <script>
                        var userLanguage = navigator.language || navigator.userLanguage;
                        var messages = {
                            'en': 'Authorization Failed, error: %1',
                            'zh-CN': '授权失败，错误信息：%1'
                        };
                        var messageText = document.getElementById('messageText');
                        if (messages[userLanguage]) {
                            messageText.textContent = messages[userLanguage];
                        }
                    </script>
                </body>
                </html>
                )");

static QString genCodeChallengeS256(QStringView code_verifier) {
    auto sha256 = QCryptographicHash::hash(code_verifier.toUtf8(), QCryptographicHash::Sha256);
    return QString::fromLatin1(
        sha256.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));
}

[[maybe_unused]] static QString generateCryptoRandomString(quint8 length) {
    // FIXME
    // !!! SEVERE SECURITY WARNING !!!
    // 当前实现的熵池可能不满足密码学的要求

    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static std::random_device randomEngine;
    std::uniform_int_distribution<int> distribution(0, sizeof(characters) - 2);
    QByteArray data;
    data.reserve(length);
    for (quint8 i = 0; i < length; ++i)
        data.append(characters[distribution(randomEngine)]);
    return data;
}

void LoginController::setup_server() {
    if (login_redirect_server)
        return;
    login_redirect_server = new QHttpServer;
    login_redirect_server->route("/", [this](const QHttpServerRequest& request) {
        // OAuth 2.0 Redirect Uri
        auto status_code = QHttpServerResponder::StatusCode::Ok;
        QString errorDescription;

        switch (request.method()) {
        case QHttpServerRequest::Method::Get: {
            auto query = request.query();
            // check for state
            if (!query.hasQueryItem("state")) {
                status_code = QHttpServerResponder::StatusCode::BadRequest;
                break;
            }
            auto state = query.queryItemValue("state");
            if (state != this->state) {
                status_code = QHttpServerResponder::StatusCode::BadRequest;
                break;
            }
            this->state.clear(); // Clear State, as it should be used only once

            // check for error
            if (query.hasQueryItem("error")) {
                errorDescription = query.hasQueryItem("error_description")
                                       ? query.queryItemValue("error_description")
                                       : query.queryItemValue("error");
                emit loginFailed(errorDescription);
                status_code = QHttpServerResponder::StatusCode::BadRequest;
                break;
            }

            // check for code
            if (query.hasQueryItem("code")) {
                auto code = query.queryItemValue("code");
                getRepo()->loginViaSastLink(code).then([this](EventoResult<DTO_User> result) {
                    if (!result) {
                        emit loginFailed(result.message());
                        return;
                    }
                    UserHelper::getInstance()->updateUser(result.take());
                    emit loginSuccess();
                });
                break;
            }

            // otherwise
            status_code = QHttpServerResponder::StatusCode::BadRequest;
        } break;
        case QHttpServerRequest::Method::Options:
            break;
        default:
            status_code = QHttpServerResponder::StatusCode::BadRequest;
            break;
        }

        QHttpServerResponse resp(QHttpServerResponder::StatusCode::InternalServerError);
        if (status_code == QHttpServerResponder::StatusCode::Ok)
            resp = QHttpServerResponse("text/html", OK_RESPONSE, status_code);
        else
            resp = QHttpServerResponse("text/html", ERROR_RESPONSE.arg(errorDescription).toUtf8(),
                                       status_code);
        resp.setHeader("Access-Control-Allow-Origin", "https://link.sast.fun");
        resp.setHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
        resp.setHeader("Access-Control-Allow-Headers",
                       "Origin, Content-Type, Accept, Authorization");
        return resp;
    });
    login_redirect_server->listen(QHostAddress::LocalHost, 1919);
}

LoginController* LoginController::create(QQmlEngine*, QJSEngine*) {
    static LoginController singleton;
    QJSEngine::setObjectOwnership(&singleton, QQmlEngine::CppOwnership);
    return &singleton;
}

void LoginController::beginLoginViaSastLink() {
    setup_server();
    // FIXME
    // !!! SEVERE SECURITY WARNING !!!
    // !!! THIS MUST BE FIXED BEFORE RELEASED !!!
    // Evento 后端目前只支持固定为 sast_forever，这导致 code 可以不经过 native 程序处理便被劫持使用
    // 来自浏览器端的攻击可以直接拦截到账号权限，而不需要对 native 程序进行攻击。
    // 潜在的 code 泄露漏洞。
    this->code_verifier = QStringLiteral("sast_forever");
    // 根据 RFC 规定：
    // with a minimum length of 43 characters and a maximum length of 128 characters.
    // https://datatracker.ietf.org/doc/html/rfc7636#section-4.1
    // this->code_verifier = generateCryptoRandomString(64);

    // FIXME
    // !!! SEVERE SECURITY WARNING !!!
    // !!! THIS MUST BE FIXED BEFORE RELEASED !!!
    // SASTLink 目前只支持固定为 xyz，这导致我们无法检查会话 ID，
    // 这可能导致预期之外的请求被 native 程序处理，潜在的 RCE 漏洞利用源。
    this->state = QStringLiteral("xyz");
    // this->state = generateCryptoRandomString(8);

    QUrl url(AUTH_SERVER_URL);
    QUrlQuery query;
    query.addQueryItem("client_id", AUTH_CLIENT_ID);
    query.addQueryItem("code_challenge", genCodeChallengeS256(code_verifier));
    query.addQueryItem("code_challenge_method", "S256");
    query.addQueryItem("redirect_uri", "http://localhost:1919/");
    query.addQueryItem("response_type", "code");
    query.addQueryItem("scope", "all");
    query.addQueryItem("state", state);
    url.setQuery(query);

    QDesktopServices::openUrl(url);

    emit loginProcessing();
}

void LoginController::loadPermissionList() {
    getRepo()
        ->getAdminPermission()
        .then([this](EventoResult<QStringList> result) {
            if (!result) {
                auto message = result.message();
                if (message.contains("No valid permission exist")) {
                    UserHelper::getInstance()->setProperty("permission",
                                                           UserHelper::Permission::UserPermission);
                    emit loadPermissionSuccessEvent();
                } else {
                    emit loadPermissionErrorEvent(message);
                }
                return;
            }
            auto permissionList = result.take();
            UserHelper::getInstance()->setProperty("permission",
                                                   UserHelper::Permission::AdminPermission);
            emit loadPermissionSuccessEvent();
        })
        .then(std::bind(&LoginController::close_tcp_listen, this));
}
