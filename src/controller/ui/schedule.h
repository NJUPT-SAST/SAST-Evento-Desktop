#ifndef SCHEDULE_CONTROLLER_H
#define SCHEDULE_CONTROLLER_H

#include "evento_exception.h"

#include <QtQml>

class ScheduleController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)
    QML_SINGLETON

    Q_PROPERTY(int height MEMBER m_height NOTIFY widthChanged)

public:
    Q_INVOKABLE void loadRegisteredSchedule();
    Q_INVOKABLE void loadSubscribedSchedule();
    Q_INVOKABLE void check(const int eventId, const QString& code, bool refreshAll = true);

signals:
    void loadRegisteredScheduleSuccessEvent();
    void loadRegisteredScheduleErrorEvent(QString message);

    void loadSubscribedScheduleSuccessEvent();
    void loadSubscribedScheduleErrorEvent(QString message);

    void checkSuccessEvent(bool refreshAll);
    void checkErrorEvent(QString message);

private:
    ScheduleController() = default;

    int m_height;

public:
    void onLoadRegisteredFinished() {
        emit loadRegisteredScheduleSuccessEvent();
    }
    void onLoadRegisteredFailure(const QString& msg) {
        emit loadRegisteredScheduleErrorEvent(msg);
    }
    void onLoadSubscribedFinished() {
        emit loadSubscribedScheduleSuccessEvent();
    }
    void onLoadSubscribedFailure(const QString& msg) {
        emit loadSubscribedScheduleErrorEvent(msg);
    }
    void checkFinished(bool refreshAll) {
        emit checkSuccessEvent(refreshAll);
    }
    void checkFailure(const QString& msg) {
        emit checkErrorEvent(msg);
    }

public:
    static ScheduleController* getInstance();
    static ScheduleController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

signals:
    void widthChanged();
};

#endif // SCHEDULE_CONTROLLER_H
