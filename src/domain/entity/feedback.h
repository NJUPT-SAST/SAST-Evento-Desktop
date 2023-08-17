#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "types.h"

struct Feedback
{
    int id;
    int score;
    QString content;
    QString userId;
    EventoID eventId;
};

#endif // FEEDBACK_H
