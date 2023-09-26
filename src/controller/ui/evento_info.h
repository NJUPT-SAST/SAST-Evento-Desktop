#ifndef EVENTO_INFO_H
#define EVENTO_INFO_H

#include <QtQml>

#include "types.h"

class EventoInfoController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoInfoController)
    QML_SINGLETON

    Q_PROPERTY(bool isRegistrated MEMBER m_isRegistrated NOTIFY isRegistratedChanged)
    Q_PROPERTY(bool isParticipated MEMBER m_isParticipated NOTIFY isParticipatedChanged)
    Q_PROPERTY(bool isSubscribed MEMBER m_isSubscribed NOTIFY isSubscribedChanged)
    Q_PROPERTY(bool editable MEMBER m_editable NOTIFY editableChanged)

public:
    Q_INVOKABLE void loadEventoInfo(EventoID id);
    Q_INVOKABLE void registerEvento(EventoID id, bool selection);
    Q_INVOKABLE void subscribeEvento(EventoID id, bool selection);
    Q_INVOKABLE void feedbackEvento(QString content, int score, EventoID id);

private:
    bool m_isRegistrated;
    bool m_isParticipated;
    bool m_isSubscribed;
    bool m_editable;

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(QString message);

    void registerSuccessEvent();
    void registerErrorEvent(QString message);

    void subscribeSuccessEvent();
    void subscribeErrorEvent(QString message);

    void feedbackSuccessEvent();
    void feedbackErrorEvent(QString message);

    void isRegistratedChanged();
    void isParticipatedChanged();
    void isSubscribedChanged();
    void editableChanged();

private:
    EventoInfoController() = default;
public:
    void onLoadFinished() {
        emit loadEventoSuccessEvent();
    }
    void onLoadFailure(const QString& msg) {
        emit loadEventoErrorEvent(msg);
    }
    void onRegisterFinished() {
        emit registerSuccessEvent();
    }
    void onRegisterFailure(const QString& msg) {
        emit registerErrorEvent(msg);
    }
    void onSubscribeFinished() {
        emit subscribeSuccessEvent();
    }
    void onSubscribeFailure(const QString& msg) {
        emit subscribeErrorEvent(msg);
    }
    void onFeedbackFinished() {
        emit feedbackSuccessEvent();
    }
    void onFeedbackFailure(const QString& msg) {
        emit feedbackErrorEvent(msg);
    }

    static EventoInfoController *getInstance();
    static EventoInfoController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_INFO_H
