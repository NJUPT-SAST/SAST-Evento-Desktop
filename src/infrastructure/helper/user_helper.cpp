#include "user_helper.h"
#include "user.h"

UserHelper *UserHelper::getInstance()
{
    static UserHelper instance;
    return &instance;
}

UserHelper *UserHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return getInstance();
}

void UserHelper::updateUser(const User &user)
{
    id = user.id;
    name = user.name;
    avatar = user.avatar;
    department = user.department;
    description = user.description;
    email = user.email;
    link = user.link;
}

