#ifndef EVENTOCALENDAR_H
#define EVENTOCALENDAR_H

#include <QObject>
#include "src/controller/eventoblockmodel.h"

class EventoCalendar : public QObject
{
    Q_OBJECT

public:
    using EventoID = QString;

    enum CalendarMode{
        Overall = 0,
        Mine = 1
    };

    static EventoCalendar* getInstance();

    ~EventoCalendar() = default;

public slots:
    void onClick(EventoID);
    void onMove(EventoID, int, int);

private:
    EventoCalendar();

    EventoBlockModel* m_eventoBlockModel;
};

#endif // EVENTOCALENDAR_H
