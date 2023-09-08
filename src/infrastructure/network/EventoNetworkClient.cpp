#include "EventoNetworkClient.h"

static const QUrl API_GATEWAY("https://sast-evento.example.com/");
constexpr const char *USER_AGENT = "SAST-Evento-Desktop/1";
constexpr const char *MIME_FORM_URL_ENCODED = "application/x-www-form-urlencoded";
constexpr const char *MIME_JSON = "application/json";

EventoNetworkClient::EventoNetworkClient()
{
}

static QFuture<std::variant<QJsonValue, EventoException>> handleNetworkReply(QNetworkReply *reply)
{
    QFuture<void> onFinishedFuture = QtFuture::connect(reply, &QNetworkReply::finished);
    return onFinishedFuture.then([reply]() -> std::variant<QJsonValue, EventoException> {
        auto networkError = reply->error();
        if (networkError != QNetworkReply::NoError) {
            return EventoException(EventoExceptionCode::NetworkError, "network error");
        }
        QJsonParseError jsonError;
        auto result = QJsonDocument::fromJson(reply->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            return EventoException(EventoExceptionCode::JsonError,
                                   QStringLiteral("json error: %1 (offest = %2)").arg(jsonError.errorString(), jsonError.offset));
        }
        reply->deleteLater();
        if (!result.isObject()) {
            return EventoException(EventoExceptionCode::JsonError, QStringLiteral("expect object but got other"));
        }
        QJsonObject jsonObject = result.object();
        auto successItem = jsonObject.constFind("success");
        if (successItem != jsonObject.constEnd() && successItem.value().toBool()) {
            // successful
            auto dataItem = jsonObject.constFind("data");
            if (dataItem != jsonObject.constEnd()) {
                return static_cast<QJsonValue>(dataItem.value());
            }
            return QJsonValue{};
        } else {
            // error
            auto errCodeItem = jsonObject.constFind("errCode");
            auto errMsgItem = jsonObject.constFind("errMsg");
            EventoExceptionCode errCode = EventoExceptionCode::UnexpectedError;
            QString errMsg = QStringLiteral("no error message");
            if (errCodeItem != jsonObject.constEnd()) {
                errCode = static_cast<EventoExceptionCode>(errCodeItem.value().toInt(
                    static_cast<int>(EventoExceptionCode::UnexpectedError)));
            }
            if (errMsgItem != jsonObject.constEnd()) {
                errMsg = errMsgItem.value().toString(errMsg);
            }
            return EventoException(errCode, errMsg);
        }
    });
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::get(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.get(request);
    return handleNetworkReply(reply);
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint)
{
    return API_GATEWAY.resolved(QUrl(endpoint));
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint, const QUrlQuery &params)
{
    auto r = API_GATEWAY.resolved(QUrl(endpoint));
    r.setQuery(params);
    return r;
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::post(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.post(request, requestData);
    return handleNetworkReply(reply);
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::post(const QUrl &url, const QUrlQuery &requestData)
{
    return this->post(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::post(const QUrl &url, const QJsonDocument &requestData)
{
    return this->post(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::put(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.put(request, requestData);
    return handleNetworkReply(reply);
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::put(const QUrl &url, const QUrlQuery &requestData)
{
    return this->put(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::put(const QUrl &url, const QJsonDocument &requestData)
{
    return this->put(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::patch(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.sendCustomRequest(request, "PATCH", requestData);
    return handleNetworkReply(reply);
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::patch(const QUrl &url, const QUrlQuery &requestData)
{
    return this->patch(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::patch(const QUrl &url, const QJsonDocument &requestData)
{
    return this->patch(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<std::variant<QJsonValue, EventoException>> EventoNetworkClient::deleteResource(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.deleteResource(request);
    return handleNetworkReply(reply);
}

QFuture<std::variant<DTO_User, EventoException>> EventoNetworkClient::getUserInfo(const UserID &id)
{
    auto url = endpoint(QStringLiteral("/user/info"), [&](QUrlQuery params) {
        params.addQueryItem("userId", id);
    });
    return this->get(url).then([](std::variant<QJsonValue, EventoException> result) -> std::variant<DTO_User, EventoException> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            // FIXME
            return DTO_User{};
        } else {
            return std::get<EventoException>(result);
        }
    });
}