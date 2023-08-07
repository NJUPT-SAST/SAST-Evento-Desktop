#ifndef LANG_H
#define LANG_H

#include <QObject>
#include "../stdafx.h"

class Lang : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,lang_plaza);
    Q_PROPERTY_AUTO(QString,lang_schedule);
    Q_PROPERTY_AUTO(QString,lang_history);
    Q_PROPERTY_AUTO(QString,lang_souvenir_card);
    Q_PROPERTY_AUTO(QString,lang_manage);
    Q_PROPERTY_AUTO(QString,lang_my);
    Q_PROPERTY_AUTO(QString,lang_theming);
    Q_PROPERTY_AUTO(QString,lang_dark_mode);
    Q_PROPERTY_AUTO(QString,lang_sys_dark_mode);
    Q_PROPERTY_AUTO(QString,lang_search);
    Q_PROPERTY_AUTO(QString,lang_settings);
    Q_PROPERTY_AUTO(QString,lang_navigation_view_display_mode);
    Q_PROPERTY_AUTO(QString,lang_locale);
    Q_PROPERTY_AUTO(QString,lang_profile);
    Q_PROPERTY_AUTO(QString,lang_check);

    Q_PROPERTY_AUTO(QString,lang_create_event);
    Q_PROPERTY_AUTO(QString,lang_event_info);
    Q_PROPERTY_AUTO(QString,lang_timesheet);
    Q_PROPERTY_AUTO(QString,lang_user_manage);
    Q_PROPERTY_AUTO(QString,lang_feedback);
    Q_PROPERTY_AUTO(QString,lang_upload_souvenir_card);
    Q_PROPERTY_AUTO(QString,lang_slide);
    Q_PROPERTY_AUTO(QString,lang_others);

    Q_PROPERTY_AUTO(QString,lang_welcome);
    Q_PROPERTY_AUTO(QString,lang_login);
    Q_PROPERTY_AUTO(QString,lang_comment);
    Q_PROPERTY_AUTO(QString,lang_submit);
    Q_PROPERTY_AUTO(QString,lang_subscribe);
    Q_PROPERTY_AUTO(QString,lang_unsubscribe);
    Q_PROPERTY_AUTO(QString,lang_checked);
    Q_PROPERTY_AUTO(QString,lang_undertaking);
    Q_PROPERTY_AUTO(QString,lang_not_started);
    Q_PROPERTY_AUTO(QString,lang_over);
    Q_PROPERTY_AUTO(QString,lang_undertaking_evento);
    Q_PROPERTY_AUTO(QString,lang_latest_evento);
    Q_PROPERTY_AUTO(QString,lang_username);
    Q_PROPERTY_AUTO(QString,lang_password);
    Q_PROPERTY_AUTO(QString,lang_zh);
    Q_PROPERTY_AUTO(QString,lang_en);
    Q_PROPERTY_AUTO(QString,lang_participate_in);
    Q_PROPERTY_AUTO(QString,lang_cancel);
    Q_PROPERTY_AUTO(QString,lang_exit);
    Q_PROPERTY_AUTO(QString,lang_determine_exit);

    Q_PROPERTY_AUTO(QString,lang_followSystem);
    Q_PROPERTY_AUTO(QString,lang_light);
    Q_PROPERTY_AUTO(QString,lang_dark);

    Q_PROPERTY_AUTO(QString,lang_openSideBar);
    Q_PROPERTY_AUTO(QString,lang_compactSideBar);
    Q_PROPERTY_AUTO(QString,lang_minimalSideBar);
    Q_PROPERTY_AUTO(QString,lang_automatical);
public:
    explicit Lang(QObject *parent = nullptr);

};

#endif // LANG_H
