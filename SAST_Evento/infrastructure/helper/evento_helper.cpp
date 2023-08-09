#include "evento_helper.h"

EventoHelper* EventoHelper::m_instance = nullptr;

EventoHelper::EventoHelper(QObject *parent)
{

}

EventoHelper *EventoHelper::getInstance()
{
    if (EventoHelper::m_instance == nullptr) {
        EventoHelper::m_instance = new EventoHelper;
    }
    return EventoHelper::m_instance;
}
