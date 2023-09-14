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
    setProperty("id", feedback.id);
    setProperty("score", feedback.score);
    setProperty("content", feedback.content);
    setProperty("eventId", feedback.eventId);
    setProperty("submitted", feedback.submitted);
}
