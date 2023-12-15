#ifndef FEEDBACK_STATISTICS_CONTROLLER_H
#define FEEDBACK_STATISTICS_CONTROLLER_H

#include <QtQml>

#include "types.h"

class FeedbackStatisticsController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadSummaryInfo(int page);
    Q_INVOKABLE void loadFeedbackInfo(EventoID id);

signals:
    void loadSummarySuccessEvent(int sum);
    void loadSummaryErrorEvent(QString message);

    void loadFeedbackSuccessEvent();
    void loadFeedbackErrorEvent(QString massage);

private:
    FeedbackStatisticsController() = default;

public:
    void onLoadSummaryFinished(const int sum) {
        emit loadSummarySuccessEvent(sum);
    }
    void onLoadSummaryFailure(const QString& msg) {
        emit loadSummaryErrorEvent(msg);
    }
    void onLoadFeedbackFinished() {
        emit loadFeedbackSuccessEvent();
    }
    void onLoadFeedbackFailure(const QString& msg) {
        emit loadFeedbackErrorEvent(msg);
    }

    static FeedbackStatisticsController* getInstance();
    static FeedbackStatisticsController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
};

#endif // FEEDBACKSTATISTICSCONTROLLER_H
