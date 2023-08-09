#ifndef EVENTOCONTROLLER_H
#define EVENTOCONTROLLER_H

#include "application/service/feedbackservice.h"
#include "application/service/eventservice.h"
#include "application/service/slideimageservice.h"
#include "basecontroller.h"

class EventoController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoController)
    Q_PROPERTY_AUTO(int, EventStatus)
    Q_PROPERTY_AUTO(int, CheckStatus)

public:
    explicit EventoController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    SlideImageService* m_slideImageService() { return QInjection::Inject; }
    FeedbackService* m_feedbackService() { return QInjection::Inject; }
};

#endif // EVENTOCONTROLLER_H
