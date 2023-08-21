#include "user_management.h"
#include "dto/user_brief.h"
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
    {
        emit loadAllUserError(err.message());
        return;
    }

    emit loadAllUserSuccess();
}

UserManagementController *UserManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

UserManagementController *UserManagementController::getInstance()
{
    static UserManagementController singleton;
    return &singleton;
}