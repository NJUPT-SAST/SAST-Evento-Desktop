#ifndef FEEDBACKHELPER_H
#define FEEDBACKHELPER_H

#include <QtQml>

struct Feedback;

class FeedbackHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER id NOTIFY idChanged)
    Q_PROPERTY(int score MEMBER score NOTIFY scoreChanged)
    Q_PROPERTY(QString content MEMBER content NOTIFY contentChanged)
    Q_PROPERTY(QString userId MEMBER userId NOTIFY userIdChanged)
    Q_PROPERTY(int eventId MEMBER eventId NOTIFY eventIdChanged)

public:
    static FeedbackHelper *getInstance();

    static FeedbackHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateFeedback(const Feedback &feedback);

private:
    FeedbackHelper() = default;

    int id;
    int score;
    QString content;
    QString userId;
    int eventId;

signals:
    void idChanged();
    void scoreChanged();
    void contentChanged();
    void userIdChanged();
    void eventIdChanged();
};

#endif // FEEDBACKHELPER_H
