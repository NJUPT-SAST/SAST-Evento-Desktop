#include "eventocalendar.h"

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar instance;
    return &instance;
}
