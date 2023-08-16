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

void EventoHelper::updateEvento(const Evento &evento)
{
    m_id = evento.id;
    m_title = evento.title;
    m_state = (int)evento.state;
    m_eventTime = evento.eventTime;
    m_registerTime = evento.registerTime;
    m_department = evento.departments;
    m_location = evento.location;
    m_tag = evento.tag;
    m_description = evento.description;
    //m_buttonText =
}
