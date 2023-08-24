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
    setProperty("eventDateStart", evento.gmtEventStart.toString(QStringLiteral("yyyy-MM-dd")));
    setProperty("eventTimeStartH", evento.gmtEventStart.toString(QStringLiteral("hh")));
    setProperty("eventTimeStartM", evento.gmtEventStart.toString(QStringLiteral("mm")));
    setProperty("eventDateEnd", evento.gmtEventEnd.toString(QStringLiteral("yyyy-MM-dd")));
    setProperty("eventTimeEndH", evento.gmtEventEnd.toString(QStringLiteral("hh")));
    setProperty("eventTimeEndM", evento.gmtEventEnd.toString(QStringLiteral("mm")));
    setProperty("registerDateStart", evento.gmtRegistrationStart.toString(QStringLiteral("yyyy-MM-dd")));
    setProperty("registerTimeStartH", evento.gmtRegistrationStart.toString(QStringLiteral("hh")));
    setProperty("registerTimeStartM", evento.gmtRegistrationStart.toString(QStringLiteral("mm")));
    setProperty("registerDateEnd", evento.gmtRegistrationEnd.toString(QStringLiteral("yyyy-MM-dd")));
    setProperty("registerTimeEndH", evento.gmtRegistrationEnd.toString(QStringLiteral("hh")));
    setProperty("registerTimeEndM", evento.gmtRegistrationEnd.toString(QStringLiteral("mm")));
}
