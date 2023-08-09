#ifndef CALENDARCONTROLLER_H
#define CALENDARCONTROLLER_H

#include "basecontroller.h"
#include "application/service/eventservice.h"

class CalendarController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CalendarController)
    Q_PROPERTY_AUTO(int, calenderMode)

public:
    enum class CalendaerMode {
        Overall = 0,
        Mine = 1
    };

    explicit CalendarController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
};

#endif // CALENDARCONTROLLER_H
