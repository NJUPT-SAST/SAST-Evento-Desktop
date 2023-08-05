#include "eventoedit.h"

std::mutex EventoEdit::m_mutex;

EventoEdit *EventoEdit::getInstance()
{
    static EventoEdit instance;
    return &instance;
}
