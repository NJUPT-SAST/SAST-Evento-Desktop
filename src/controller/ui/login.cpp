#include "login.h"

LoginController *LoginController::create(QQmlEngine *, QJSEngine *)
{
    static LoginController instance;
    return &instance;
}

void LoginController::login(const QString &username, const QString &password)
{

}
