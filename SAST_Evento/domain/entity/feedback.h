#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eventobase.h"

struct Feedback : EventoBase
{
    QString time;
    int score;
    QString content;
};

#endif // FEEDBACK_H
