#include "user_service.h"
#include "evento_info.h"
#include "repository.h"
#include "schedule.h"
#include <QtConcurrent>
#include <array>

void UserService::checkIn(EventoID eventId, const QString& code) {
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

void UserService::subscribeEvento(EventoID id, bool selection) {
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

void UserService::registerEvento(EventoID id, bool selection) {
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
