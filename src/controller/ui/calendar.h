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
    Q_INVOKABLE void loadCheckCode(const EventoID eventId);

signals:
    void loadAllEventoSuccessEvent();
    void loadAllEventoErrorEvent(QString message);

    void deleteSuccessEvent();
    void deleteErrorEvent(QString message);

    void cancelSuccessEvent();
    void cancelErrorEvent(QString message);

    void loadCheckCodeSuccessEvent(QString code);
    void loadCheckCodeErrorEvent(QString message);

private:
    CalendarController() = default;
public:
    void onLoadAllFinished() {
        emit loadAllEventoSuccessEvent();
    }
    void onLoadAllFailure(const QString& message) {
        emit loadAllEventoErrorEvent(message);
    }
    void onDeleteFinished() {
        emit deleteSuccessEvent();
    }
    void onDeleteFailure(const QString& message) {
        emit deleteErrorEvent(message);
    }
    void onCancelFinished() {
        emit cancelSuccessEvent();
    }
    void onCancelFailure(const QString& message) {
        emit cancelErrorEvent(message);
    }
    void onLoadCheckCodeFinished(const QString& code) {
        emit loadCheckCodeSuccessEvent(code);
    }
    void onLoadCheckCodeFailure(const QString& message) {
        emit loadCheckCodeErrorEvent(message);
    }

    static CalendarController *getInstance();
    static CalendarController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // CALENDARCONTROLLER_H
