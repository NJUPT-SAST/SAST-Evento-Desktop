#ifndef DTO_FEEDBACK_H
#define DTO_FEEDBACK_H

#include "types.h"

struct DTO_Feedback {
    int id;
    EventoID eventId;
    int score;
    QString content;
};

#endif // DTO_FEEDBACK_H
