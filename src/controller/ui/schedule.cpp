#include "schedule.h"
#include "evento_service.h"
#include "user_service.h"
#include "local/repositoryimpl.h"

void ScheduleController::loadRegisteredSchedule()
{
    EventoService::getInstance().load_RegisteredSchedule();
}

void ScheduleController::loadSubscribedSchedule()
{
    EventoService::getInstance().load_SubscribedSchedule();
}

void ScheduleController::check(const int eventId, const QString &code)
{
    UserService::getInstance().checkIn(eventId, code);
}

ScheduleController *ScheduleController::getInstance()
{
    static ScheduleController instance;
    return &instance;
}

ScheduleController *ScheduleController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
