#ifndef EVENTOEDITCONTROLLER_H
#define EVENTOEDITCONTROLLER_H

#include "basecontroller.h"
#include "application/service/eventservice.h"
#include "application/service/slideimageservice.h"

class EventoEditController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)

public:
    explicit EventoEditController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    SlideImageService* m_slideImageService() { return QInjection::Inject; }
};

#endif // EVENTOEDITCONTROLLER_H
