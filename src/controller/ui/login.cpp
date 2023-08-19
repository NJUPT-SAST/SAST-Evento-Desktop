#include "login.h"
#include "local/repositoryimpl.h"

LoginController::LoginController(QObject *parent)
    : m_repository(new repositoryImpl)
{

}

void LoginController::login(const QString &username, const QString &password)
{

}

LoginController::~LoginController() = default;
