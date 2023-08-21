#include "login.h"

LoginController *LoginController::create(QQmlEngine *, QJSEngine *)
{
	return new LoginController();
}

void LoginController::login(const QString &username, const QString &password)
{

}
