#ifndef FEEDBACK_STATISTICS_CONTROLLER_H
#define FEEDBACK_STATISTICS_CONTROLLER_H

 #include <QtQml>

class FeedbackStatisticsController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsController)

public:
    explicit FeedbackStatisticsController(QObject *parent = nullptr) {}
};

#endif // FEEDBACKSTATISTICSCONTROLLER_H
