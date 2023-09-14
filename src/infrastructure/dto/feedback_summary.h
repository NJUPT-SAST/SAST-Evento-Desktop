#ifndef DTO_FEEDBACK_SUMMARY_H
#define DTO_FEEDBACK_SUMMARY_H

#include "types.h"

#include <dto/feedback.h>

struct DTO_FeedbackSummary
{
    EventoID eventId;
    int subscribedNum;
    int registeredNum;
    int checkedNum;
    QString aveScore;
    std::vector<DTO_Feedback> feedbacks;
};

#endif // DTO_FEEDBACK_SUMMARY_H
