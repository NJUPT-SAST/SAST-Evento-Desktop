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
    Q_INVOKABLE void registerEvento(EventoID id, bool isParticipated);
    Q_INVOKABLE void subscribeEvento(EventoID id, bool isParticipated);
    Q_INVOKABLE void feedbackEvento(const QString& content, const int score, const EventoID id);

private:
    bool m_isRegistrated;
    bool m_isParticipated;
    bool m_isSubscribed;
    bool m_editable;

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString message);

    void registerSuccessEvent();
    void registerErrorEvent(const QString message);

    void subscribeSuccessEvent();
    void subscribeErrorEvent(const QString message);

    void feedbackSuccessEvent();
    void feedbackErrorEvent(const QString message);

    void isRegistratedChanged();
    void isParticipatedChanged();
    void isSubscribedChanged();
    void editableChanged();

private:
    EventoInfoController() = default;
public:
    void onLoadSuccess() {
        emit loadEventoSuccessEvent();
    }
    void onLoadFailure(const QString& msg) {
        emit loadEventoErrorEvent(msg);
    }
public:
    static EventoInfoController *getInstance();
    static EventoInfoController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_INFO_H
