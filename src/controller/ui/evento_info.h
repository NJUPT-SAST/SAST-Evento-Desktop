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
    Q_INVOKABLE void loadEventoInfo(EventoID id);

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString &message);

public:
    EventoInfoController() = default;
    static EventoInfoController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_INFO_H
