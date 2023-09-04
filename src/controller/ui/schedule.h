#ifndef SCHEDULE_CONTROLLER_H
#define SCHEDULE_CONTROLLER_H

#include <QtQml>

class ScheduleController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadRegisteredSchedule();
    Q_INVOKABLE void loadSubscribedSchedule();
    Q_INVOKABLE void check(const int eventId, const QString &code);

signals:
    void loadRegisteredScheduleSuccessEvent();
    void loadRegisteredScheduleErrorEvent(const QString message);

    void loadSubscribedScheduleSuccessEvent();
    void loadSubscribedScheduleErrorEvent(const QString message);

    void checkSuccessEvent();
    void checkErrorEvent(const QString &message);

public:
    ScheduleController() = default;
    static ScheduleController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // SCHEDULE_CONTROLLER_H
