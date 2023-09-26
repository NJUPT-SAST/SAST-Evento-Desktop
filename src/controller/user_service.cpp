#include "user_service.h"
#include "repository.h"
#include "schedule.h"
#include "evento_info.h"
#include "login.h"
#include "user_helper.h"
#include <QtConcurrent>
#include <array>

void UserService::checkIn(EventoID eventId, const QString &code)
{
    getRepo()->checkIn(eventId, code).then([=](EventoResult<bool> result) {
        if (!result) {
            ScheduleController::getInstance()->checkFailure(result.message());
            return;
        }
        ScheduleController::getInstance()->checkFinished();
    });
}

void UserService::subscribeEvento(EventoID id, bool selection)
{
    getRepo()->subscribeEvent(id, selection).then([=](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onSubscribeFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onSubscribeFinished();
    });
}

void UserService::registerEvento(EventoID id, bool selection)
{
    getRepo()->registerEvent(id, selection).then([=](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onRegisterFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onRegisterFinished();
    });
}

void UserService::getSelfPermission()
{
    auto future = getRepo()->getAdminPermission().then([](EventoResult<QStringList> result) {
        if (!result) {
            LoginController::getInstance()->onLoadPermissionFailure(result.message());
            return false;
        }
        auto permissionList = result.take();
        if (permissionList.isEmpty())
            UserHelper::getInstance()->setProperty("permission", UserHelper::Permission::UserPermission);
        else
            UserHelper::getInstance()->setProperty("permission", UserHelper::Permission::AdminPermisson);
        return true;
    });
    QtConcurrent::run([=] {
        auto f(future);
        auto result = f.takeResult();
        if (result)
            LoginController::getInstance()->onLoadPermissionFinished();
    });
}
