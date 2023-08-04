#include "eventoedit.h"

EventoEdit::EventoEdit()
{

}

EventoEdit *EventoEdit::getInstance()
{
    static EventoEdit instance;
    return &instance;
}


