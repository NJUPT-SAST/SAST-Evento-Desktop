#include "user_service.h"
#include "evento_info.h"
#include "repository.h"
#include "schedule.h"

void UserService::checkIn(EventoID eventId, const QString& code, bool refreshAll) {
    getRepo()->checkIn(eventId, code).then([=](EventoResult<bool> result) {
        if (!result) {
            ScheduleController::getInstance()->checkFailure(result.message());
            return;
        }
        ScheduleController::getInstance()->checkFinished(refreshAll);
    });
}

void UserService::subscribeEvento(EventoID id, bool selection) {
    getRepo()->subscribeEvent(id, selection).then([](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onSubscribeFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onSubscribeFinished();
    });
}

void UserService::registerEvento(EventoID id, bool selection) {
    getRepo()->registerEvent(id, selection).then([](EventoResult<bool> result) {
        if (!result) {
            EventoInfoController::getInstance()->onRegisterFailure(result.message());
            return;
        }
        EventoInfoController::getInstance()->onRegisterFinished();
    });
}
