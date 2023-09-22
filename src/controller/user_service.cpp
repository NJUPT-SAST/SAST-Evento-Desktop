#include "user_service.h"
#include "evento_service.h"
#include "repository.h"
#include "schedule.h"
#include "evento_info.h"
#include <QtConcurrent>
#include <array>

void UserService::checkIn(const int eventId, const QString &code)
{
    auto future = getRepo()->checkIn(eventId, code);
    future.waitForFinished();
    auto result = future.takeResult();
    if (result)
        ScheduleController::getInstance()->checkFinished();
    else
        ScheduleController::getInstance()->checkFailure(result.message());
}

void UserService::subscribeEvento(EventoID id, bool selection)
{
    emit EventoInfoController::getInstance()->subscribeSuccessEvent();
}

void UserService::registerEvento(const EventoID id, bool selection)
{
    emit EventoInfoController::getInstance()->registerSuccessEvent();
}

void UserService::load_EventoInfo(const EventoID eventId)
{
    EventoException err;

    auto participate = getRepo()->getUserParticipate(eventId, err);
    if (err)
        return emit EventoInfoController::getInstance()->loadEventoErrorEvent(err.message());

    EventoInfoController::getInstance()->setProperty("isRegistrated", participate.isRegistrated);
    EventoInfoController::getInstance()->setProperty("isParticipated", participate.isParticipated);
    EventoInfoController::getInstance()->setProperty("isSubscribed", participate.isSubscribed);

    EventoService::getInstance().load(eventId);
}

