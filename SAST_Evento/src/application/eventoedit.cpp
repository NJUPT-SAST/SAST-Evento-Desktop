#include "eventoedit.h"

EventoEdit *EventoEdit::getInstance()
{
    static EventoEdit instance;
    return &instance;
}
