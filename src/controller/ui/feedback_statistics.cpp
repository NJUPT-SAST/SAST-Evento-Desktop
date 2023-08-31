#include "feedback_statistics.h"
#include "convertor.h"
#include "evento_exception.h"

void FeedbackStatisticsController::loadFeedbackInfo(int page)
{
    EventoException err;
    //getRepo()->get_feedback_info(page, 10);
    if ((int) err.code())
        return emit loadFeedbackErrorEvent(err.message());
    emit loadFeedbackSuccessEvent();
}

FeedbackStatisticsController *FeedbackStatisticsController::create(QQmlEngine *qmlEngine,
                                                                   QJSEngine *jsEngine)
{
    return new FeedbackStatisticsController();
}
