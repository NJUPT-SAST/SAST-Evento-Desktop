#include "feedback_statistics_helper.h"
#include "dto/feedback_summary.h"

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

void FeedbackStatisticsHelper::updateFeedbackStatistics(const DTO_FeedbackSummary &e)
{
    setProperty("registerNum", e.registerNum);
    setProperty("checkedNum", e.checkedNum);
    setProperty("aveScore", e.aveScore);
}
