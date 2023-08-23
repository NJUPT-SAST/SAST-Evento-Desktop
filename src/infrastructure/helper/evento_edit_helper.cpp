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
    m_departmentJson = departmentJson;
    m_locationJson = locationJson;
    m_typeJson = typeJson;
    m_departmentIds.clear();
    for (const auto& department : evento.departments) {
        m_departmentIds.append(department.id);
    }
    m_typeId = evento.type.id;
    m_allowConflict = evento.type.allowConflict;
}
