#ifndef USERMANAGEMENT_CONTROLLER_H
#define USERMANAGEMENT_CONTROLLER_H

 #include <QtQml>
#include "repository.h"

class UserManagementController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserManagementController)

public:
    UserManagementController() = default;

    Q_INVOKABLE void loadAllUserInfo();

signals:
    void loadAllUserSuccess();
    void loadAllUserError();

private:
    Repository* m_repository;
};

#endif // USERMANAGEMENT_CONTROLLER_H
