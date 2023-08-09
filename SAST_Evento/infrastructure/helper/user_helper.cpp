#include "user_helper.h"

UserHelper* UserHelper::m_instance = nullptr;

UserHelper *UserHelper::getInstance()
{
    if(UserHelper::m_instance == nullptr){
        UserHelper::m_instance = new UserHelper;
    }
    return UserHelper::m_instance;
}

UserHelper::UserHelper(QObject* parent) : QObject{ parent }
{
    token(SettingsHelper::getInstance()->getToken());
}
