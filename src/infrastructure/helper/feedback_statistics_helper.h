#ifndef FEEDBACKSTATISTICSHELPER_H
#define FEEDBACKSTATISTICSHELPER_H

#include <QtQml>

struct DTO_FeedbackSummary;

class FeedbackStatisticsHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsHelper)
    QML_SINGLETON

    Q_PROPERTY(int registerNum MEMBER m_registerNum NOTIFY registerNumChanged)
    Q_PROPERTY(int checkedNum MEMBER m_checkedNum NOTIFY checkedNumChanged)
    Q_PROPERTY(QString aveScore MEMBER m_aveScore NOTIFY aveScoreChanged)

public:
    static FeedbackStatisticsHelper *getInstance();

    static FeedbackStatisticsHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateFeedbackStatistics(const DTO_FeedbackSummary &e);

private:
    FeedbackStatisticsHelper() = default;

    int m_registerNum;
    int m_checkedNum;
    QString m_aveScore;

signals:
    void registerNumChanged();
    void checkedNumChanged();
    void aveScoreChanged();
};

#endif // FEEDBACKSTATISTICSHELPER_H
