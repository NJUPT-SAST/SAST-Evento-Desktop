#include "feedback_helper.h"
#include "feedback.h"

FeedbackHelper *FeedbackHelper::getInstance()
{
    static FeedbackHelper instance;
    return &instance;
}

FeedbackHelper *FeedbackHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return getInstance();
}

void FeedbackHelper::updateFeedback(const Feedback &feedback)
{
    id = feedback.id;
    score = feedback.score;
    content = feedback.content;
    userId = feedback.userId;
    eventId = feedback.eventId;
}
