#include "eventocalendar.h"

<<<<<<< HEAD
std::mutex EventoCalendar::m_mutex;
=======
EventoCalendar::EventoCalendar()
{

}
>>>>>>> 3bfb64fcdf3908b652e3f7c0bba0156365ab0447

EventoCalendar *EventoCalendar::getInstance()
{
    static EventoCalendar instance;
    return &instance;
}
