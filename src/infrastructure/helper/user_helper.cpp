#include "user_helper.h"
#include "user.h"

UserHelper *UserHelper::getInstance()
{
    static UserHelper instance;
    return &instance;
}

UserHelper *UserHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void UserHelper::updateUser(const User &user)
{
    setProperty("id", user.id);
    setProperty("name", user.name);
    setProperty("avatar", user.avatar);
    setProperty("department", user.department);
    setProperty("description", user.description);
    setProperty("email", user.email);
    setProperty("link", user.link);
}

