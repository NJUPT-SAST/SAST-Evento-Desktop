#include "feedback_statistics.h"
#include "feedback_service.h"

void FeedbackStatisticsController::loadSummaryInfo(int page) {
    FeedbackService::getInstance().load_SummaryInfo(page);
}

void FeedbackStatisticsController::loadFeedbackInfo(EventoID id) {
    FeedbackService::getInstance().load_FeedbackInfo(id);
}

FeedbackStatisticsController* FeedbackStatisticsController::getInstance() {
    static FeedbackStatisticsController instance;
    return &instance;
}

FeedbackStatisticsController* FeedbackStatisticsController::create(QQmlEngine* qmlEngine,
                                                                   QJSEngine* jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
