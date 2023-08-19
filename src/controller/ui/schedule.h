#ifndef SCHEDULE_CONTROLLER_H
#define SCHEDULE_CONTROLLER_H

#include <QtQml>

class Repository;

class ScheduleController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)

public:
    explicit ScheduleController(QObject *parent = nullptr);
    ~ScheduleController();
    Q_INVOKABLE void loadSchedule();
    Q_INVOKABLE void check(const int eventId, const QString& code);

signals:
    void loadScheduleSuccessEvent();
    void loadScheduleErrorEvent(const QString& message);

    void checkSuccessEvent();
    void checkErrorEvent(const QString& message);

private:
    std::unique_ptr<Repository> m_repository;
};

#endif // SCHEDULE_CONTROLLER_H
