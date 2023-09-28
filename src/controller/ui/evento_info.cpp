#include "evento_info.h"
#include "evento_service.h"
#include "feedback_service.h"
#include "user_service.h"

void EventoInfoController::loadEventoInfo(EventoID eventId) {
    EventoService::getInstance().load(eventId);
}

void EventoInfoController::registerEvento(EventoID id, bool selection) {
    UserService::getInstance().registerEvento(id, selection);
}

void EventoInfoController::feedbackEvento(QString content, int score, EventoID id) {
    FeedbackService::getInstance().feedback(id, score, content);
}

void EventoInfoController::subscribeEvento(EventoID id, bool selection) {
    UserService::getInstance().subscribeEvento(id, selection);
}

EventoInfoController* EventoInfoController::getInstance() {
    static EventoInfoController instance;
    return &instance;
}

EventoInfoController* EventoInfoController::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
