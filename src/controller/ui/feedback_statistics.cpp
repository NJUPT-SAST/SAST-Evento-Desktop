#include "feedback_statistics.h"
#include "convertor.h"
#include "evento_exception.h"

int FeedbackStatisticsController::loadSummaryInfo(int page)
{
    EventoException err;
    // TODO
    if ((int) err.code()) {
        emit loadSummaryErrorEvent(err.message());
        return 0;
    }
    emit loadSummarySuccessEvent();
    return 30;
}

void FeedbackStatisticsController::loadFeedbackInfo()
{
    EventoException err;
    if ((int) err.code())
        return emit loadFeedbackErrorEvent(err.message());
    emit loadFeedbackSuccessEvent();
}

FeedbackStatisticsController *FeedbackStatisticsController::create(QQmlEngine *qmlEngine,
                                                                   QJSEngine *jsEngine)
{
    return new FeedbackStatisticsController();
}
