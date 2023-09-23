#ifndef FEEDBACKSERVICE_H
#define FEEDBACKSERVICE_H

#include "feedback.h"
#include <dto/feedback_summary.h>

#include <QFuture>
#include <shared_mutex>

class FeedbackService
{
    std::shared_mutex mutex;
    Feedback userfeedback;
    std::map<int, Feedback> feedbacks;

private:
    FeedbackService() = default;
public:
    static FeedbackService& getInstance() {
        static FeedbackService singleton;
        return singleton;
    }

    void load_UserFeedback(EventoID id);
    void load_FeedbackInfo(EventoID id);
    void load_SummaryInfo(int page);
};

#endif // FEEDBACKSERVICE_H
