#ifndef FEEDBACKHELPER_H
#define FEEDBACKHELPER_H

#include <QtQml>

struct Feedback;

class FeedbackHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(int score MEMBER m_score NOTIFY scoreChanged)
    Q_PROPERTY(QString content MEMBER m_content NOTIFY contentChanged)
    Q_PROPERTY(int eventId MEMBER m_eventId NOTIFY eventIdChanged)
    Q_PROPERTY(bool isFeedback MEMBER m_isFeedback NOTIFY isFeedbackChanged)

public:
    static FeedbackHelper *getInstance();

    static FeedbackHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateFeedback(const Feedback &feedback);

private:
    FeedbackHelper() = default;

    int m_id;
    int m_score;
    QString m_content;
    int m_eventId;
    bool m_isFeedback;

signals:
    void idChanged();
    void scoreChanged();
    void contentChanged();
    void eventIdChanged();
    void isFeedbackChanged();
};

#endif // FEEDBACKHELPER_H
