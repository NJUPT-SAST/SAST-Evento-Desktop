#ifndef FEEDBACK_SUMMARY_H
#define FEEDBACK_SUMMARY_H

#include "types.h"
struct DTO_FeedbackSummary;

struct FeedbackSummary
{
    EventoID eventId;
    QString title;
    int subscribedNum;
    int registeredNum;
    int checkedNum;
    int feedbackNum;
    QString aveScore;

    FeedbackSummary() = default;
    FeedbackSummary(const DTO_FeedbackSummary&);
    FeedbackSummary(const std::pair<int,int>&);
    //first data is eventoId,second data is feedbackCount
};

#endif // FEEDBACK_SUMMARY_H
