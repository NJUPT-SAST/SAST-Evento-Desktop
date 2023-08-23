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
    m_id = user.id;
    m_name = user.name;
    m_avatar = user.avatar;
    m_department = user.department;
    m_description = user.description;
    m_email = user.email;
    m_link = user.link;
}

