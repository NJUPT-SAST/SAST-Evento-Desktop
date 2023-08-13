#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <QtQML>

enum class LoginStatus : int {
    Start = 1,
    Loading,
    Success,
    Failed
};

class LoginController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(LoginController)
    QML_SINGLETON

    Q_PROPERTY(int loginStatus MEMBER status NOTIFY loginStatusChanged)

private:
    int status = int(LoginStatus::Start);
signals:
    void loginStatusChanged();
public:
    Q_INVOKABLE void login(const QString& username, const QString& password) {}
    LoginController() = default;
};

#endif // LOGIN_CONTROLLER_H
