#ifndef EVENTOCALENDAR_H
#define EVENTOCALENDAR_H

#include <QObject>

class EventoCalendar
{
    Q_OBJECT

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
<<<<<<< HEAD
    static std::mutex m_mutex;

    EventoCalendar(){};
    ~EventoCalendar(){};
    EventoCalendar(const EventoCalendar&);
    EventoCalendar &operator=(const EventoCalendar&);
=======
    EventoCalendar();
>>>>>>> 3bfb64fcdf3908b652e3f7c0bba0156365ab0447
};

#endif // EVENTOCALENDAR_H
