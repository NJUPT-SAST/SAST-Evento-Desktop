#ifndef USERMANAGEMENT_CONTROLLER_H
#define USERMANAGEMENT_CONTROLLER_H

#include <QtQML>

class UserManagementController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserManagementController)

public:
    explicit UserManagementController(QObject *parent = nullptr) {}
};

#endif // USERMANAGEMENT_CONTROLLER_H
