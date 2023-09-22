#include "evento_info.h"
#include "repository.h"
#include "evento_service.h"
#include "evento_exception.h"
#include "user_service.h"
#include "feedback_helper.h"
#include "slide_model.h"

void EventoInfoController::loadEventoInfo(const EventoID eventId)
{
    UserService::getInstance().load_EventoInfo(eventId);
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
