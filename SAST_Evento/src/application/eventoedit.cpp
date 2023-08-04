#include "eventoedit.h"

EventoEdit::EventoEdit()
{

}

std::mutex EventoEdit::m_mutex;

EventoEdit *EventoEdit::getInstance()
{
    static EventoEdit* instance = nullptr;
    if (instance)
        return instance;
    std::lock_guard<std::mutex> lck(m_mutex);
    if (!instance)
        instance = new EventoEdit();
    return instance;
}


