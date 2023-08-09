#ifndef MYPAGECONTROLLER_H
#define MYPAGECONTROLLER_H

#include "application/service/eventservice.h"
#include "application/service/slideimageservice.h"
#include "application/service/userservice.h"
#include "basecontroller.h"

class MyPageController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MyPageController)

public:
    explicit MyPageController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    SlideImageService* m_slideImageService() { return QInjection::Inject; }
    UserService* m_userService() { return QInjection::Inject; }
};

#endif // MYPAGECONTROLLER_H
