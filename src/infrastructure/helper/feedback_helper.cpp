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
    m_id = feedback.id;
    m_score = feedback.score;
    m_content = feedback.content;
    m_eventId = feedback.eventId;
    m_isFeedback = feedback.isFeedback;
}
