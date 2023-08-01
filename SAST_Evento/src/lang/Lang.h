#ifndef LANG_H
#define LANG_H

#include <QObject>
#include "../stdafx.h"

class Lang : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,home);
    Q_PROPERTY_AUTO(QString,schedule);
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
    Q_PROPERTY_AUTO(QString,personalData);
    Q_PROPERTY_AUTO(QString,sign_in);

    Q_PROPERTY_AUTO(QString,createEvent);
    Q_PROPERTY_AUTO(QString,eventInfo);
    Q_PROPERTY_AUTO(QString,timesheet);
    Q_PROPERTY_AUTO(QString,usermanage);
    Q_PROPERTY_AUTO(QString,feedback);
    Q_PROPERTY_AUTO(QString,uploadSouvenirCard);
    Q_PROPERTY_AUTO(QString,ppt);

    Q_PROPERTY_AUTO(QString,welcome);

    Q_PROPERTY_AUTO(QString,zh);
    Q_PROPERTY_AUTO(QString,en);

    Q_PROPERTY_AUTO(QString,followSystem);
    Q_PROPERTY_AUTO(QString,light);
    Q_PROPERTY_AUTO(QString,dark);

    Q_PROPERTY_AUTO(QString,openSideBar);
    Q_PROPERTY_AUTO(QString,compactSideBar);
    Q_PROPERTY_AUTO(QString,minimalSideBar);
    Q_PROPERTY_AUTO(QString,automatical);
public:
    explicit Lang(QObject *parent = nullptr);

};

#endif // LANG_H
