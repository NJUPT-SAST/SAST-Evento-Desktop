#include "scheduled_evento.h"
#include "schedule.h"
#include "scheduled_evento_model.h"
#include "convertor.h"

void ScheduleController::loadRegisteredSchedule()
{
    auto future = getRepo()->getRegisteredList();
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result)
        return emit loadRegisteredScheduleErrorEvent(result.message());

    ScheduledEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<Schedule>>()(result.take()));

    emit loadRegisteredScheduleSuccessEvent();
}

void ScheduleController::loadSubscribedSchedule()
{
    auto future = getRepo()->getSubscribedList();
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result)
    {
        emit loadSubscribedScheduleErrorEvent(result.message());
        return;
    }
    ScheduledEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>,
                    std::vector<Schedule>>()(result.take()));

    emit loadSubscribedScheduleSuccessEvent();
}

void ScheduleController::check(const int eventId, const QString &code)
{
    auto future = getRepo()->checkIn(eventId, code);
    future.waitForFinished();
    auto result = future.takeResult();
    if (result)
        emit checkSuccessEvent();
    else
        emit checkErrorEvent(result.message());
}

ScheduleController *ScheduleController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new ScheduleController();
}
