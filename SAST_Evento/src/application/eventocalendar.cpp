#include "eventocalendar.h"

std::mutex EventoCalendar::m_mutex;

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar instance;
    return &instance;
}
