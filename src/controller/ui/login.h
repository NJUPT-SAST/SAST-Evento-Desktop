#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <QtQML>

class LoginController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(LoginController)
    QML_SINGLETON

    Q_PROPERTY(int loginStatus MEMBER status NOTIFY loginStatusChanged)

private:
    int status;
signals:
    void loginStatusChanged();
public:
    enum class Status {
        Start = 1,
        Loading,
        Success,
        Failed
    };

    explicit LoginController(QObject* parent = nullptr) {}
    Q_INVOKABLE void login(const QString& username, const QString& password) {}
};

#endif // LOGIN_CONTROLLER_H
