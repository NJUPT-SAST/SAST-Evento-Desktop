#include "eventocalendar.h"

EventoCalendar::EventoCalendar()
{

}

std::mutex EventoCalendar::m_mutex;

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar* instance = nullptr;
    if (instance)
        return instance;
    std::lock_guard<std::mutex> lck(m_mutex);
    if (!instance)
        instance = new EventoCalendar();
    return instance;
}
