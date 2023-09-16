#ifndef FEEDBACK_SUMMARY_H
#define FEEDBACK_SUMMARY_H

#include "types.h"

struct FeedbackSummary
{
    EventoID eventId;
    QString title;
    int subscribedNum;
    int registeredNum;
    int checkedNum;
    int feedbackNum;
    QString aveScore;
};

#endif // FEEDBACK_SUMMARY_H
