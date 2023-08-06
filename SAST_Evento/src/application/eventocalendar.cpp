#include "eventocalendar.h"

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar instance;
    return &instance;
}

EventoCalendar::EventoCalendar() : m_eventoBlockModel(EventoBlockModel::getInstance())
{

}
