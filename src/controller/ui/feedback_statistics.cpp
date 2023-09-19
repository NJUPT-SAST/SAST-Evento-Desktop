#include "feedback_statistics.h"
#include "evento_exception.h"

void FeedbackStatisticsController::loadSummaryInfo(int page)
{
    EventoException err;
    // TODO
    if ((int) err.code()) {
        return emit loadSummaryErrorEvent(err.message());
    }
    emit loadSummarySuccessEvent(30);
}

void FeedbackStatisticsController::loadFeedbackInfo()
{
    EventoException err;
    if ((int) err.code())
        return emit loadFeedbackErrorEvent(err.message());
    emit loadFeedbackSuccessEvent();
}

FeedbackStatisticsController *FeedbackStatisticsController::getInstance()
{
    static FeedbackStatisticsController instance;
    return &instance;
}

FeedbackStatisticsController *FeedbackStatisticsController::create(QQmlEngine *qmlEngine,
                                                                   QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
