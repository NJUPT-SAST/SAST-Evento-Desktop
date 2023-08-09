#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "application/service/userservice.h"
#include "basecontroller.h"

using namespace QInjection;

class LoginController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,loginStatus)
    QML_NAMED_ELEMENT(LoginController)

public:
    enum class Status {
        Start = 1,
        Loading,
        Success,
        Failed
    };

    explicit LoginController(QObject* parent = nullptr);
    Q_INVOKABLE void login(const QString& username, const QString& password);

private:
    UserService* m_userService() { return QInjection::Inject; }
};

#endif // LOGINCONTROLLER_H
