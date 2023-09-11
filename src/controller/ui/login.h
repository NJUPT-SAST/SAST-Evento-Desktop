#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <QtQml>
#include <QHttpServer>

class LoginController : public QObject
{
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
    void loginFailed(const QString &reason);

public:
    static LoginController *create(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE void beginLoginViaSastLink();

    LoginController();
};

#endif // LOGIN_CONTROLLER_H
