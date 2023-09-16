#include "evento_edit.h"
#include "evento_service.h"
#include "repository.h"

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
    EventoException err;
    auto departmentList = getRepo()->getDepartmentList(err);
    if (err)
        return emit loadEditErrorEvent(err.message());
    auto locationList = getRepo()->getLocationList(err);
    if (err)
        return emit loadEditErrorEvent(err.message());
    auto typeList = getRepo()->getTypeList(err);
    if (err)
        return emit loadEditErrorEvent(err.message());

    setProperty("departmentJson", departmentList);
    setProperty("locationJson", locationList);
    setProperty("typeJson", typeList);
}

void EventoEditController::editEvento(EventoID id) {
    preload();
    setProperty("isEditMode", true);
    update(EventoService::getInstance().edit(id));
    emit loadEditSuccessEvent();
}

void EventoEditController::update(const DTO_Evento& event) {
    setProperty("allowConflict", event.type.allowConflict);
    setProperty("eventStart", event.gmtEventStart);
    setProperty("eventEnd", event.gmtEventEnd);
    setProperty("registerStart", event.gmtRegistrationStart);
    setProperty("registerEnd", event.gmtRegistrationEnd);
}

void EventoEditController::createEvento()
{
    preload();
    setProperty("isEditMode", false);
    emit createSuccessEvent();
}
