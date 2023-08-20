#ifndef EVENTO_INFO_H
#define EVENTO_INFO_H

#include <QtQml>
#include "types.h"

class EventoInfoController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoInfoController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadEventoInfo(const EventoID id);
    Q_INVOKABLE void registerEvento(const EventoID id, bool isParticipated);
    Q_INVOKABLE void subscribeEvento(const EventoID id, bool isParticipated);
    Q_INVOKABLE void feedbackEvento(const QString& content, const int score, const EventoID id);

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString &message);

    void registerSuccessEvent();
    void registerErrorEvent(const QString &message);

    void subscribeSuccessEvent();
    void subscribeErrorEvent(const QString &message);

    void feedbackSuccessEvent();
    void feedbackErrorEvent(const QString &message);

public:
    EventoInfoController() = default;
    static EventoInfoController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_INFO_H
