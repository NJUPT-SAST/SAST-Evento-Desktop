#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include "basecontroller.h"
#include "application/service/userservice.h"

class ProfileController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ProfileController)

public:
    explicit ProfileController(QObject *parent = nullptr);
    Q_INVOKABLE void loadProfileInfo();
    Q_SIGNAL void loadProfileSuccessEvent();
    Q_SIGNAL void loadProfileErrorEvent(const QString& message);

private:
    UserService* m_userService(){return QInjection::Inject;}
};

#endif // PROFILECONTROLLER_H
