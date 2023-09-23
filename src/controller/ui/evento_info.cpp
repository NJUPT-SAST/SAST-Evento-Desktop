#include "evento_info.h"
#include "evento_service.h"
#include "user_service.h"

void EventoInfoController::loadEventoInfo(const EventoID eventId)
{
    EventoService::getInstance().load(eventId);
}

void EventoInfoController::registerEvento(const EventoID id, bool selection)
{
    UserService::getInstance().registerEvento(id, selection);
}

void EventoInfoController::feedbackEvento(const QString &content, const int score, const EventoID id)
{
    emit feedbackSuccessEvent();
}

void EventoInfoController::subscribeEvento(const EventoID id, bool selection)
{
    UserService::getInstance().subscribeEvento(id, selection);
}

EventoInfoController *EventoInfoController::getInstance()
{
    static EventoInfoController instance;
    return &instance;
}

EventoInfoController *EventoInfoController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
