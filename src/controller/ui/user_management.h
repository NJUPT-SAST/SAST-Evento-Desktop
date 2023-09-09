#ifndef USERMANAGEMENT_CONTROLLER_H
#define USERMANAGEMENT_CONTROLLER_H

#include <QtQml>

class UserManagementController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(UserManagementController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadAllUserInfo();

signals:
    void loadAllUserSuccess();
    void loadAllUserError(const QString message);

public:
    UserManagementController() = default;
    static UserManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // USERMANAGEMENT_CONTROLLER_H
