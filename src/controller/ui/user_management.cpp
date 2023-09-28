#include "user_management.h"
#include "user_brief_model.h"

// deprecated

void UserManagementController::loadAllUserInfo() {
    emit loadAllUserSuccess();
}

QString UserManagementController::loadPermissionInfo() {
    return {};
}

void UserManagementController::createUser(const QVariantList& list) {
    // TODO
    emit createSuccessEvent();
}

UserManagementController* UserManagementController::create(QQmlEngine* qmlEngine,
                                                           QJSEngine* jsEngine) {
    
    return new UserManagementController();
}

void UserManagementController::updateUserId(QString id) {
    UserManagementController::userId = id;
}

QString UserManagementController::getUserId() {
    return userId;
}

void UserManagementController::updateIsEdit(bool isEdit) {
    UserManagementController::m_isEdit = isEdit;
}

bool UserManagementController::getIsEdit() {
    return UserManagementController::m_isEdit;
}
