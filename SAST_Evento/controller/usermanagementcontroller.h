#ifndef USERMANAGEMENTCONTROLLER_H
#define USERMANAGEMENTCONTROLLER_H

#include "basecontroller.h"
#include "application/service/userservice.h"

class UserManagementController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(UserManagementController)

public:
    explicit UserManagementController(QObject *parent = nullptr);

private:
    UserService* m_userService() { return QInjection::Inject; }
};

#endif // USERMANAGEMENTCONTROLLER_H
