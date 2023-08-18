#ifndef USERHELPER_H
#define USERHELPER_H

#include <QtQml>
#include <QStringList>
#include <QString>

struct User;

class UserHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserHelper)
    QML_SINGLETON

    Q_PROPERTY(QString id MEMBER id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
    Q_PROPERTY(QString avatar MEMBER avatar NOTIFY avatarChanged)
    Q_PROPERTY(QStringList department MEMBER department NOTIFY departmentChanged)
    Q_PROPERTY(QString description MEMBER description NOTIFY descriptionChanged)
    Q_PROPERTY(QString email MEMBER email NOTIFY emailChanged)
    Q_PROPERTY(QStringList link MEMBER link NOTIFY linkChanged)

public:
    static UserHelper *getInstance();

    static UserHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateUser(const User &user);

    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /  (Perhaps a get function is missing)  /
    /                                       /
    /                                       /
    /--------------------------------------*/
private:
    UserHelper() = default;

    QString id;
    QString name;
    QString avatar;
    QStringList department;
    QString description;
    QString email;
    QStringList link;

signals:
    void idChanged();
    void nameChanged();
    void avatarChanged();
    void departmentChanged();
    void descriptionChanged();
    void emailChanged();
    void linkChanged();
};

#endif // USERHELPER_H
