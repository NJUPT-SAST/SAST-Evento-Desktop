#include "user_management.h"
#include "convertor.h"
#include "user_brief_model.h"

void UserManagementController::loadAllUserInfo()
{
    EventoException err;
    // 获取DTO_User_Brief并交由对应Convertor转换为Model赋值给实例
    //    UserBriefModel::getInstance()->resetModel(
    //        Convertor<std::vector<DTO_UserBrief>,
    //                  std::vector<UserBrief>>()(
    //            getRepo()->get_user_brief_list(err)
    //    ));
    if ((int)err.code())
        return emit loadAllUserError(err.message());

    emit loadAllUserSuccess();
}

QString UserManagementController::loadPermissionInfo()
{
    EventoException err;
    auto result = getRepo()->get_admin_permission_treeData(err);

    if ((int)err.code()){
        emit loadPermissionErrorEvent(err.message());
        return {};
    }
    emit loadPermissionSuccessEvent();
    return result;
}

void UserManagementController::createUser(const QVariantList& list)
{
    // TODO
    emit createSuccessEvent();
}

UserManagementController *UserManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new UserManagementController();
}

 void UserManagementController::updateUserId(QString id)
 {
    UserManagementController::userId = id;
 }

 QString UserManagementController::getUserId()
 {
    return userId;
 }

 void UserManagementController::updateIsEdit(bool isEdit)
 {
    UserManagementController::m_isEdit = isEdit;
 }

 bool UserManagementController::getIsEdit()
 {
    return UserManagementController::m_isEdit;
 }


