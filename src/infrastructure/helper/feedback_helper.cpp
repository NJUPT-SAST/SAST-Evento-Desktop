#include "feedback_helper.h"
#include "feedback.h"

FeedbackHelper *FeedbackHelper::getInstance()
{
    static FeedbackHelper instance;
    return &instance;
}

FeedbackHelper *FeedbackHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void FeedbackHelper::updateFeedback(const Feedback &feedback)
{
    m_id = feedback.id;
    m_score = feedback.score;
    m_content = feedback.content;
    m_userId = feedback.userId;
    m_eventId = feedback.eventId;
}
