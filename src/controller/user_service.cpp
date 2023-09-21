#include "user_service.h"
#include "convertor.h"
#include "evento.h"
#include "repository.h"
#include "schedule.h"
#include "scheduled_evento_model.h"
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
