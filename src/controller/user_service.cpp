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
    auto future = getRepo()->checkIn(eventId, code).then([=](EventoResult<bool> result) {
        if (!result) {
            ScheduleController::getInstance()->checkFailure(result.message());
            return;
        }
        ScheduleController::getInstance()->checkFinished();
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}

void UserService::subscribeEvento(EventoID id, bool selection)
{
    auto future = getRepo()->subscribeEvent(id, selection).then([=](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onSubscribeFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onSubscribeFinished();
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}

void UserService::registerEvento(EventoID id, bool selection)
{
    auto future = getRepo()->registerEvent(id, selection).then([=](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onRegisterFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onRegisterFinished();
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}

void UserService::getSelfPermission()
{
    auto future = getRepo()->getAdminPermission().then([](EventoResult<QStringList> result) {
        if (!result) {
            LoginController::getInstance()->onLoadPermissionFailure(result.message());
            return;
        }
        auto permissionList = result.take();
        if (permissionList.isEmpty())
            UserHelper::getInstance()->setProperty("permission", UserHelper::Permission::UserPermission);
        else
            UserHelper::getInstance()->setProperty("permission", UserHelper::Permission::AdminPermisson);
        LoginController::getInstance()->onLoadPermissionFinished();
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}
