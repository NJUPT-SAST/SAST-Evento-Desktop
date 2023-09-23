#ifndef FEEDBACKSTATISTICSHELPER_H
#define FEEDBACKSTATISTICSHELPER_H

#include <QtQml>

struct FeedbackSummary;

class FeedbackStatisticsHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsHelper)
    QML_SINGLETON

    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
    Q_PROPERTY(int registerNum MEMBER m_registerNum NOTIFY registerNumChanged)
    Q_PROPERTY(int checkedNum MEMBER m_checkedNum NOTIFY checkedNumChanged)
    Q_PROPERTY(int subscribedNum MEMBER m_subscribedNum NOTIFY subscribedNumChanged)
    Q_PROPERTY(QString aveScore MEMBER m_aveScore NOTIFY aveScoreChanged)

public:
    static FeedbackStatisticsHelper *getInstance();

    static FeedbackStatisticsHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateFeedbackStatistics(const FeedbackSummary &e);

private:
    FeedbackStatisticsHelper() = default;

    QString m_title;
    int m_registerNum;
    int m_checkedNum;
    int m_subscribedNum;
    QString m_aveScore;

signals:
    void titleChanged();
    void registerNumChanged();
    void checkedNumChanged();
    void subscribedNumChanged();
    void aveScoreChanged();
};

#endif // FEEDBACKSTATISTICSHELPER_H
