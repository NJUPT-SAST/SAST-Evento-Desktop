#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H

#include "application/service/eventservice.h"
#include "application/service/slideimageservice.h"
#include "basecontroller.h"

class ScheduleController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScheduleController)

public:
    explicit ScheduleController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    SlideImageService* m_slideImageService() { return QInjection::Inject; }
};

#endif // SCHEDULECONTROLLER_H
