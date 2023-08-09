#ifndef USER_H
#define USER_H

#include <QStringList>

struct User
{
    QString id;
    QString name;
    QString avatar;
    QString image;
    QStringList department;
    QString description;
    QString email;
    QStringList link;
};

#endif // USER_H
