#include "eventoedit.h"

<<<<<<< HEAD
std::mutex EventoEdit::m_mutex;
=======
EventoEdit::EventoEdit()
{

}
>>>>>>> 3bfb64fcdf3908b652e3f7c0bba0156365ab0447

EventoEdit *EventoEdit::getInstance()
{
    static EventoEdit instance;
    return &instance;
}
