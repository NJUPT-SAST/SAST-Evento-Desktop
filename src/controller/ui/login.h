#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <QHttpServer>
#include <QtQml>

class LoginController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(LoginController)
    QML_SINGLETON

private:
    QHttpServer login_redirect_server;
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

    void onLoadPermissionFinished() {
        emit loadPermissionSuccessEvent();
    }
    void onLoadPermissionFailure(const QString& msg) {
        emit loadPermissionErrorEvent(msg);
    }

    LoginController();
};

#endif // LOGIN_CONTROLLER_H
