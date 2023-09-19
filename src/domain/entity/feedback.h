#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "types.h"
struct DTO_Feedback;

struct Feedback
{
    int id;
    EventoID eventId;
    int score;
    QString content;
    bool submitted = false;

    Feedback() = default;
    Feedback(const DTO_Feedback&);
};

#endif // FEEDBACK_H
