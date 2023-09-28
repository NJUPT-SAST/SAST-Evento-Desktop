#ifndef FEEDBACK_SUMMARY_H
#define FEEDBACK_SUMMARY_H

#include "types.h"

struct DTO_FeedbackSummary;

struct FeedbackSummary {
    EventoID eventId;
    QString title;
    int subscribedNum;
    int registeredNum;
    int checkedNum;
    QString aveScore;

    FeedbackSummary() = default;
    FeedbackSummary(const DTO_FeedbackSummary&, const QString& title);
};

#endif // FEEDBACK_SUMMARY_H
