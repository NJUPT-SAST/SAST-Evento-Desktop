#include "feedback_statistics_helper.h"
#include "feedback_summary.h"

FeedbackStatisticsHelper *FeedbackStatisticsHelper::getInstance()
{
    static FeedbackStatisticsHelper instance;
    return &instance;
}

FeedbackStatisticsHelper *FeedbackStatisticsHelper::create(QQmlEngine *qmlEngine,
                                                           QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void FeedbackStatisticsHelper::updateFeedbackStatistics(const FeedbackSummary &e)
{
    setProperty("registerNum", e.registeredNum);
    setProperty("checkedNum", e.checkedNum);
    setProperty("subscribedNum", e.subscribedNum);
    setProperty("feedbackNum", e.feedbackNum);
    setProperty("aveScore", e.aveScore);
}
