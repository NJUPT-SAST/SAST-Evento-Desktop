#ifndef EVENTOCALENDAR_H
#define EVENTOCALENDAR_H

#include <QObject>
#include <mutex>

class EventoCalendar
{
    //Q_OBJECT

public:
    enum CalendarMode{
        Overall = 0,
        Mine = 1
    };

    static EventoCalendar* getInstance();

public slots:
    void onClick();
    void onMove();

private:
    EventoCalendar();
    static std::mutex m_mutex;
};

#endif // EVENTOCALENDAR_H
