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

    Q_INVOKABLE void updateUserId(QString id);
    Q_INVOKABLE QString getUserId();

    Q_INVOKABLE void updateIsEdit(bool isEdit);
    Q_INVOKABLE bool getIsEdit();

signals:
    void loadAllUserSuccess();
    void loadAllUserError(const QString message);

    void loadPermissionSuccessEvent();
    void loadPermissionErrorEvent(const QString message);

    void createSuccessEvent();
    void createErrorEvent(const QString message);

public:
    UserManagementController() = default;
    static UserManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    QString userId = "null";
    bool m_isEdit = false;
};

#endif // USERMANAGEMENT_CONTROLLER_H
