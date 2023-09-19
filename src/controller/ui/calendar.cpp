#include "calendar.h"
#include "evento_exception.h"
#include "evento_info.h"
#include "repository.h"

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
    emit deleteSuccessEvent();
}

QString CalendarController::loadCheckCode(const EventoID eventId)
{
    EventoException err;
    auto code = getRepo()->getQRCode(eventId, err);
    if (err) {
        emit loadCheckCodeErrorEvent(err.message());
        return {};
    }
    emit loadCheckCodeSuccessEvent();
    return code;
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
