#include "calendar.h"
#include "evento_info.h"
#include "evento_service.h"

void CalendarController::loadAllEventoInfo(const QString &date)
{
    emit loadAllEventoSuccessEvent();
}

void CalendarController::loadEventoInfo(const EventoID eventId)
{
    EventoInfoController::getInstance()->loadEventoInfo(eventId);
}

void CalendarController::deleteEvento(const EventoID eventId)
{
    EventoService::getInstance().del(eventId);
}

void CalendarController::cancelEvento(const EventoID eventId)
{
    EventoService::getInstance().cancel(eventId);
}

void CalendarController::loadCheckCode(const EventoID eventId)
{
    EventoService::getInstance().getQRCode(eventId);
}

CalendarController *CalendarController::getInstance()
{
    static CalendarController instance;
    return &instance;
}

CalendarController *CalendarController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
