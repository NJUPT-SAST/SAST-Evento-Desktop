#ifndef PLAZACONTROLLER_H
#define PLAZACONTROLLER_H

#include "application/service/eventservice.h"
#include "application/service/slideimageservice.h"
#include "basecontroller.h"

class PlazaController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PlazaController)

public:
    explicit PlazaController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    SlideImageService* m_slideImageService() { return QInjection::Inject; }
};

#endif // PLAZACONTROLLER_H
