#include "evento_edit.h"
#include "evento_service.h"
#include "information_service.h"

EventoEditController *EventoEditController::getInstance()
{
    static EventoEditController instance;
    return &instance;
}

EventoEditController *EventoEditController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

void EventoEditController::preload() {
    InformationService::getInstance().load_EditInfo();
}

void EventoEditController::editEvento(EventoID id) {
    setProperty("isEditMode", true);
    update(EventoService::getInstance().edit(id));
    preload();
}

void EventoEditController::update(const DTO_Evento& event) {
    setProperty("allowConflict", event.type.allowConflict);
    setProperty("eventStart", event.gmtEventStart);
    setProperty("eventEnd", event.gmtEventEnd);
    setProperty("registerStart", event.gmtRegistrationStart);
    setProperty("registerEnd", event.gmtRegistrationEnd);
}

void EventoEditController::loadEditInfo()
{
    setProperty("isEditMode", false);
    preload();
}
