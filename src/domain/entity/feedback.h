#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "types.h"

struct Feedback
{
    int id;
    EventoID eventId;
    int score;
    QString content;
    bool submitted = false;
};

#endif // FEEDBACK_H
