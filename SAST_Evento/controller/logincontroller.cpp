#include "logincontroller.h"
#include "infrastructure/util/util.hpp"

LoginController::LoginController(QObject *parent)
    : BaseController{parent}
{
    loginStatus(toUType(Status::Start));
}

void LoginController::login(const QString &username, const QString &password)
{
    loginStatus(toUType(Status::Loading));
    auto result = m_userService()->login(username, password);

    if (result)
        loginStatus(toUType(Status::Success));
    else
        loginStatus(toUType(Status::Failed));
}
