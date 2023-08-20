#ifndef USERMANAGEMENT_CONTROLLER_H
#define USERMANAGEMENT_CONTROLLER_H

#include <QtQml>

class Repository;

class UserManagementController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(UserManagementController)

public:
    Q_INVOKABLE void loadAllUserInfo();

signals:
    void loadAllUserSuccess();
    void loadAllUserError(const QString &message);

public:
    UserManagementController() = default;
    ~UserManagementController() = default;
};

#endif // USERMANAGEMENT_CONTROLLER_H
