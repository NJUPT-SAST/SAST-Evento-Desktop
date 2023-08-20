#ifndef FEEDBACK_STATISTICS_CONTROLLER_H
#define FEEDBACK_STATISTICS_CONTROLLER_H

 #include <QtQml>

class FeedbackStatisticsController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsController)
    QML_SINGLETON

public:
    explicit FeedbackStatisticsController(QObject *parent = nullptr) {}
    //static FeedbackStatisticsController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // FEEDBACKSTATISTICSCONTROLLER_H
