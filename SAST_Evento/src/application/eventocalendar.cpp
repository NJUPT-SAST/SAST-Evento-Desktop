#include "eventocalendar.h"

EventoCalendar::EventoCalendar()
{

}

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar instance;
    return &instance;
}
