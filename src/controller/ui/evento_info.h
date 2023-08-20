#ifndef EVENTO_INFO_H
#define EVENTO_INFO_H

#include <QtQml>
#include "types.h"

class Repository;

class EventoInfoController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoInfoController)

public:
    Q_INVOKABLE void loadEventoInfo(EventoID id);

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString &message);

public:
    EventoInfoController() = default;
    ~EventoInfoController() = default;
};

#endif // EVENTO_INFO_H
