#ifndef DTO_FEEDBACK_H
#define DTO_FEEDBACK_H

#include "types.h"

struct DTO_Feedback {
    EventoID event;
    UserID user;
    int score;
    QString content;
    ParticipationStatus participation;
};

#endif // DTO_FEEDBACK_H
