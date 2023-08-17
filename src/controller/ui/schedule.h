#ifndef SCHEDULE_CONTROLLER_H
#define SCHEDULE_CONTROLLER_H

 #include <QtQml>

class ScheduleController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)

public:
    explicit ScheduleController(QObject *parent = nullptr) {}
};

#endif // SCHEDULE_CONTROLLER_H
