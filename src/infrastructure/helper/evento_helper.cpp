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
    title = evento.title;
    state = (int)evento.state;
    eventTime = evento.eventTime;
    registerTime = evento.registerTime;
    department = evento.department;
    location = evento.location;
    tag = evento.tag;
    type = evento.type.name;
    description = evento.description;
    //m_buttonText =
}
