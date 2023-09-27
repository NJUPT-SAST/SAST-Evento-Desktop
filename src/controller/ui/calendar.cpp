#include "calendar.h"
#include "evento_info.h"
#include "evento_service.h"
#include <evento_block_model.h>

void CalendarController::loadAllEventoInfo(QString date)
{
    EventoService::getInstance().load_Block(date);
}

void CalendarController::loadEventoInfo(EventoID eventId)
{
    EventoInfoController::getInstance()->loadEventoInfo(eventId);
}

void CalendarController::deleteEvento(EventoID eventId)
{
    EventoService::getInstance().del(eventId);
}

void CalendarController::cancelEvento(EventoID eventId)
{
    EventoService::getInstance().cancel(eventId);
}

void CalendarController::loadCheckCode(EventoID eventId)
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
