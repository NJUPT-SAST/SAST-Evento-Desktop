#include "profilecontroller.h"

#include "infrastructure/helper/user_helper.h"

ProfileController::ProfileController(QObject *parent)
    : BaseController{parent}
{

}

void ProfileController::loadProfileInfo() {
    try {
        User user = m_userService()->loadUser();
        UserHelper::getInstance()->updateUser(user);
        Q_EMIT loadProfileSuccessEvent();
    } catch(const BizException& e) {
        Q_EMIT loadProfileErrorEvent(e.message);
    }
}
