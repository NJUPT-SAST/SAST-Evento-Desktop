#ifndef LANG_H
#define LANG_H

#include <QObject>
#include "../stdafx.h"

class Lang : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,home);
    Q_PROPERTY_AUTO(QString,timeTable);
    Q_PROPERTY_AUTO(QString,history);
    Q_PROPERTY_AUTO(QString,souvenirCard);
    Q_PROPERTY_AUTO(QString,organize);
    Q_PROPERTY_AUTO(QString,manage);
    Q_PROPERTY_AUTO(QString,my);
    Q_PROPERTY_AUTO(QString,theming);
    Q_PROPERTY_AUTO(QString,dark_mode);
    Q_PROPERTY_AUTO(QString,sys_dark_mode);
    Q_PROPERTY_AUTO(QString,search);
    Q_PROPERTY_AUTO(QString,settings);
    Q_PROPERTY_AUTO(QString,navigation_view_display_mode);
    Q_PROPERTY_AUTO(QString,locale);

    Q_PROPERTY_AUTO(QString,zh);
    Q_PROPERTY_AUTO(QString,en);
public:
    explicit Lang(QObject *parent = nullptr);

};

#endif // LANG_H
