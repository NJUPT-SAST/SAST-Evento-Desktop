#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "types.h"

struct Feedback
{
    int id;
    int score;
    QString content;
    int eventId;
    bool isFeedback;
};

#endif // FEEDBACK_H
