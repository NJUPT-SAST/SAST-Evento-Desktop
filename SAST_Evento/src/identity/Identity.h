#ifndef IDENTITY_H
#define IDENTITY_H

#include <QObject>
#include "../stdafx.h"

class Identity : public QObject
{
    Q_OBJECT

    enum Authority{
        NO_LOGIN,
        USER,
        MANAGER
    };

    Q_PROPERTY_AUTO(QString, username);
    Q_PROPERTY_AUTO(QString, password);
    Q_PROPERTY_AUTO(Authority, authority);

public:
    explicit Identity(const QString& username, const QString& password, QObject *parent = nullptr);

signals:

};

#endif // IDENTITY_H
