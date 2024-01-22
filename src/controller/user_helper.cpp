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
    setProperty("userId", user.id);
    setProperty("linkId", user.linkId);
    setProperty("studentId", user.studentId);
    setProperty("email", user.email);
    setProperty("nickname", user.nickname);
    setProperty("avatar", user.avatar);
    setProperty("organization", user.organization);
    setProperty("biography", user.biography);
    setProperty("link", user.link);
}