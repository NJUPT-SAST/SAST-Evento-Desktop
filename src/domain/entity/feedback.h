#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "types.h"

struct Feedback
{
    int id;
    EventoID eventId;
    int score;
    QString content;
    bool isFeedback;
};

#endif // FEEDBACK_H
