#include "Identity.h"

Identity::Identity(const QString &username, const QString &password, QObject *parent)
    :_username(username), _password(password), _authority(NO_LOGIN), QObject{parent}
{
    if (_username.isEmpty() || _password.isEmpty()) return;

    // TODO: judge authority
    if (_username == "admin") authority(MANAGER);
    else authority(USER);
}

