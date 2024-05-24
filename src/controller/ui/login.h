#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <QHttpServer>
#include <QtQml>

class LoginController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(LoginController)
    QML_SINGLETON

private:
    QHttpServer* login_redirect_server = nullptr;
    QString state;
    QString code_verifier;

signals:
    void loginProcessing();
    void loginSuccess();
    void loginFailed(QString reason);
    void loadPermissionSuccessEvent();
    void loadPermissionErrorEvent(QString message);

public:
    static LoginController* create(QQmlEngine*, QJSEngine*);

    Q_INVOKABLE void beginLoginViaSastLink();
    Q_INVOKABLE void loadPermissionList();

    ~LoginController() {
        close_tcp_listen();
    }

private:
    void setup_server();
    inline void close_tcp_listen() {
        if (login_redirect_server) {
            login_redirect_server->deleteLater();
            login_redirect_server = nullptr;
        }
    }

    LoginController() = default;
};

#endif // LOGIN_CONTROLLER_H
