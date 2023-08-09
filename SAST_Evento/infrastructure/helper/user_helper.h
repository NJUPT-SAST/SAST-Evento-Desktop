#ifndef USERHELPER_H
#define USERHELPER_H

#include <QObject>
#include <QtQml/qqml.h>
#include "infrastructure/helper/settings_helper.h"
#include "domain/entity/user.h"
#include "stdafx.h"

class UserHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,token)
    Q_PROPERTY_AUTO(QString,id)
    Q_PROPERTY_AUTO(QString,name)
    Q_PROPERTY_AUTO(QString,avatar)
    Q_PROPERTY_AUTO(QString,image)
    Q_PROPERTY_AUTO(QStringList,department)
    Q_PROPERTY_AUTO(QString,description)
    Q_PROPERTY_AUTO(QString,email)
    Q_PROPERTY_AUTO(QStringList,link)
    QML_NAMED_ELEMENT(UserHelper)
    QML_SINGLETON

private:
    explicit UserHelper(QObject* parent = nullptr);
    static UserHelper* m_instance;

public:
    static UserHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    static UserHelper *getInstance();
    Q_INVOKABLE bool isLogin(){
        return !_token.isEmpty();
    }

    Q_INVOKABLE void logout(){
        token(""),name(""),id(""),avatar(""),image(""),department(QStringList{}),
            description(""),email(""),link(QStringList{});
        SettingsHelper::getInstance()->saveToken(_token);
    }

    Q_INVOKABLE void login(const QString& val){
        token(val);
        SettingsHelper::getInstance()->saveToken(_token);
    }

    void updateUser(const User& user){
        name(user.name);
        avatar(user.avatar);
        id(user.id);
        email(user.email);
        image(user.image);
        department(user.department);
        description(user.description);
        email(user.email);
        link(user.link);
    };

};

#endif  // USERHELPER_H
