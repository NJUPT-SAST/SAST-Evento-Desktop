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
    Q_PROPERTY(QString userId MEMBER m_userId NOTIFY userIdChanged)
    Q_PROPERTY(int eventId MEMBER m_eventId NOTIFY eventIdChanged)

public:
    static FeedbackHelper *getInstance();

    static FeedbackHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateFeedback(const Feedback &feedback);

private:
    FeedbackHelper() = default;

    int m_id;
    int m_score;
    QString m_content;
    QString m_userId;
    int m_eventId;

signals:
    void idChanged();
    void scoreChanged();
    void contentChanged();
    void userIdChanged();
    void eventIdChanged();
};

#endif // FEEDBACKHELPER_H
