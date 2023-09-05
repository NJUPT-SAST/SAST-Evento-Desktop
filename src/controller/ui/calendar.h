#ifndef CALENDARCONTROLLER_H
#define CALENDARCONTROLLER_H

#include <QtQml>
#include "types.h"

class CalendarController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CalendarController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadAllEventoInfo(const QString &date);
    Q_INVOKABLE void loadEventoInfo(const EventoID eventId);
    Q_INVOKABLE void deleteEvento(const EventoID eventId);

signals:
    void loadAllEventoSuccessEvent();
    void loadAllEventoErrorEvent(const QString message);

    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString message);

    void deleteSuccessEvent();
    void deleteErrorEvent(const QString message);

public:
    CalendarController() = default;
    static CalendarController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // CALENDARCONTROLLER_H
