#ifndef USERHELPER_H
#define USERHELPER_H

#include <QString>
#include <QtQml>

#include "types.h"

struct DTO_User;

class UserHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserHelper)
    QML_SINGLETON

    Q_PROPERTY(UserID userId MEMBER m_id NOTIFY idChanged);
    Q_PROPERTY(QString linkId MEMBER m_linkId NOTIFY linkIdChanged);
    Q_PROPERTY(QString studentId MEMBER m_studentId NOTIFY studentIdChanged);
    Q_PROPERTY(QString email MEMBER m_email NOTIFY emailChanged);
    Q_PROPERTY(QString nickname MEMBER m_nickname NOTIFY nicknameChanged);
    Q_PROPERTY(QString avatar MEMBER m_avatar NOTIFY avatarChanged);
    Q_PROPERTY(QString organization MEMBER m_organization NOTIFY organizationChanged);
    Q_PROPERTY(QString biography MEMBER m_biography NOTIFY biographyChanged);
    Q_PROPERTY(QString link MEMBER m_link NOTIFY linkChanged);
    Q_PROPERTY(int permission MEMBER m_permission NOTIFY permissionChanged);

public:
    enum Permission {
        VisitorPermission = 1,
        UserPermission,
        AdminPermission,
    };

    static UserHelper* getInstance();
    static UserHelper* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    void updateUser(const DTO_User& user);

private:
    UserHelper() = default;

    UserID m_id;
    QString m_linkId;
    QString m_studentId;
    QString m_email;
    QString m_nickname;
    QString m_avatar;
    QString m_organization;
    QString m_biography;
    QString m_link;
    int m_permission = Permission::VisitorPermission;

signals:
    void idChanged();
    void linkIdChanged();
    void studentIdChanged();
    void emailChanged();
    void nicknameChanged();
    void avatarChanged();
    void organizationChanged();
    void biographyChanged();
    void linkChanged();
    void permissionChanged();
};

#endif // USERHELPER_H