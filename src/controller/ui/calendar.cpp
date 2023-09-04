#include "calendar.h"
#include "evento_exception.h"

void CalendarController::loadAllEventoInfo(const QString &date)
{
    emit loadAllEventoSuccessEvent();
}

void CalendarController::loadEventoInfo(const EventoID id)
{
    emit loadEventoSuccessEvent();
}

CalendarController *CalendarController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new CalendarController();
}
