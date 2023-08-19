#include "evento_helper.h"
#include "evento.h"

EventoHelper *EventoHelper::getInstance()
{
    static EventoHelper instance;
    return &instance;
}

EventoHelper *EventoHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return getInstance();
}

void EventoHelper::updateEvento(const Evento &evento,
                                const bool isRegistrated,
                                const bool isParticipated,
                                const bool isSubscribed,
                                const bool isfeedback)
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
    m_isRegistrated = isRegistrated;
    m_isParticipated = isParticipated;
    m_isSubscribed = isSubscribed;
    m_isfeedback = isfeedback;
}
