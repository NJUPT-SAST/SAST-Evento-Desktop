#include "user_helper.h"
#include "dto/user.h"

UserHelper* UserHelper::getInstance() {
    static UserHelper instance;
    return &instance;
}

UserHelper* UserHelper::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void UserHelper::updateUser(const DTO_User& user) {
    setProperty("userId", user.userId);
    setProperty("wechatId", user.wechatId);
    setProperty("email", user.email);
}
