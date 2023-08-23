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

void EventoHelper::updateEvento(const Evento &evento, const ParticipationStatus &participationStatus)
{
    m_title = evento.title;
    m_state = (int)evento.state;
    m_eventTime = evento.eventTime;
    m_registerTime = evento.registerTime;
    m_department = evento.department;
    m_location = evento.location;
    m_tag = evento.tag;
    m_type = evento.type.name;
    m_description = evento.description;
    m_isRegistrated = participationStatus.isRegistrated;
    m_isParticipated = participationStatus.isParticipated;
    m_isSubscribed = participationStatus.isSubscribed;
}
