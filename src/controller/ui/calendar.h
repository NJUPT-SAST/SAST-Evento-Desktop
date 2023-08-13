#ifndef CALENDAR_CONTROLLER_H
#define CALENDAR_CONTROLLER_H

#include <QtQML>

class CalendarController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(CalendarController)
    QML_SINGLETON

    Q_PROPERTY(int calenderMode MEMBER mode NOTIFY modeChnaged)

private:
    int mode;
signals:
    void modeChnaged();
public:
    enum class CalendaerMode {
        Overall = 0,
        Mine = 1
    };

    explicit CalendarController(QObject *parent = nullptr) {}
};

#endif // CALENDARCONTROLLER_H
