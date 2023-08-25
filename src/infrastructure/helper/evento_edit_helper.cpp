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
    setProperty("isEdited", true);
    if (evento.id == 0)
    {
        setProperty("isEdited", false);
        return;
    }
    // 编辑模式
    m_departmentIds.clear();
    for (const auto &department : evento.departments)
    {
        m_departmentIds.append(department.id);
    }
    setProperty("departmentIds", m_departmentIds);
    setProperty("typeId", evento.type.id);
    setProperty("allowConflict", evento.type.allowConflict);
    setProperty("eventStart", evento.gmtEventStart.toString());
    setProperty("eventEnd", evento.gmtEventEnd.toString());
    setProperty("registerStart", evento.gmtRegistrationStart.toString());
    setProperty("registerEnd", evento.gmtRegistrationEnd.toString());
}
