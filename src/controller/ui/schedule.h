#ifndef SCHEDULE_CONTROLLER_H
#define SCHEDULE_CONTROLLER_H

#include <QtQml>
#include "repository.h"

class ScheduleController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)

public:
    explicit ScheduleController(QObject *parent = nullptr);
    Q_INVOKABLE void loadSchedule(int eventId);

signals:
    void loadScheduleSuccessEvent();
    void laodScheduleErrorEvent(const QString& message);

private:
    std::unique_ptr<Repository> m_repository;
};

#endif // SCHEDULE_CONTROLLER_H
