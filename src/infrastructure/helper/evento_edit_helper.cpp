#include "evento_edit_helper.h"

EventoEditHelper *EventoEditHelper::getInstance()
{
    static EventoEditHelper instance;
    return &instance;
}

EventoEditHelper *EventoEditHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void EventoEditHelper::updateEventoEdit(const QString &departmentJson, const QString &locationJson,
                                        const QString &typeJson, const DTO_Evento &evento)
{
    setProperty("departmentJson", departmentJson);
    setProperty("locationJson", locationJson);
    setProperty("typeJson", typeJson);
    if (property("isEdited") == false)
        return;
    // edit mode
    setProperty("typeId", evento.type.id);
    setProperty("allowConflict", evento.type.allowConflict);
    setProperty("eventStart", evento.gmtEventStart.toString("yyyy年MM月dd日 HH:mm:ss"));
    setProperty("eventEnd", evento.gmtEventEnd.toString("yyyy年MM月dd日 HH:mm:ss"));
    setProperty("registerStart", evento.gmtRegistrationStart.toString("yyyy年MM月dd日 HH:mm:ss"));
    setProperty("registerEnd", evento.gmtRegistrationEnd.toString("yyyy年MM月dd日 HH:mm:ss"));
}
