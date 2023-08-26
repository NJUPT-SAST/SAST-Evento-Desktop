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
    Q_INVOKABLE QString loadPermissionInfo();
    Q_INVOKABLE void createUser(const QVariantList& list);

signals:
    void loadAllUserSuccess();
    void loadAllUserError(const QString& message);

    void loadPermissionSuccessEvent();
    void loadPermissionErrorEvent(const QString& message);

    void createSuccessEvent();
    void createErrorEvent(const QString& message);

public:
    UserManagementController() = default;
    static UserManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // USERMANAGEMENT_CONTROLLER_H
