#ifndef FEEDBACK_STATISTICS_CONTROLLER_H
#define FEEDBACK_STATISTICS_CONTROLLER_H

#include <QtQml>

class FeedbackStatisticsController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadFeedbackInfo(int page = 1);

signals:
    void loadFeedbackSuccessEvent();
    void loadFeedbackErrorEvent(const QString &message);

public:
    FeedbackStatisticsController() = default;
    static FeedbackStatisticsController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // FEEDBACKSTATISTICSCONTROLLER_H
