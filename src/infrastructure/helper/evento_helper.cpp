#include "evento_helper.h"
#include "evento.h"

EventoHelper *EventoHelper::getInstance()
{
    static EventoHelper instance;
    return &instance;
}

EventoHelper *EventoHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

bool EventoHelper::update(const Evento &evento)
{
    if (evento.id != m_id)
        return false;
    setProperty("title", evento.title);
    setProperty("state", (int)evento.state);
    setProperty("eventTime", evento.eventStart + " - " + evento.eventEnd);
    setProperty("registerTime", evento.registrationStart + " - " + evento.registrationEnd);
    setProperty("department", evento.department);
    setProperty("location", evento.location);
    setProperty("tag", evento.tag);
    setProperty("type", evento.type.name);
    setProperty("description", evento.description);
    return true;
}
