#ifndef USERHELPER_H
#define USERHELPER_H

#include <QString>
#include <QtQml>

struct DTO_User;

class UserHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserHelper)
    QML_SINGLETON

    Q_PROPERTY(QString userId MEMBER m_userId NOTIFY userIdChanged)
    Q_PROPERTY(QString wechatId MEMBER m_wechatId NOTIFY wechatIdChanged)
    Q_PROPERTY(QString email MEMBER m_email NOTIFY emailChanged)
    Q_PROPERTY(int permission MEMBER m_permission NOTIFY permissionChanged)

public:
    enum Permission {
        VisitorPermission = 1,
        UserPermission,
        AdminPermisson,
    };

    static UserHelper* getInstance();
    static UserHelper* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    void updateUser(const DTO_User& user);

private:
    UserHelper() = default;

    QString m_userId;
    QString m_wechatId;
    QString m_email;
    int m_permission;

signals:
    void userIdChanged();
    void wechatIdChanged();
    void emailChanged();
    void permissionChanged();
};

#endif // USERHELPER_H
