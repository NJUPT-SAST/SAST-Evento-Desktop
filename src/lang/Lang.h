#ifndef LANG_H
#define LANG_H

#include "stdafx.h"
#include <QObject>

class Lang : public QObject {
    Q_OBJECT
    // MainWiondow
    Q_PROPERTY_AUTO(QString, lang_hint);
    Q_PROPERTY_AUTO(QString, lang_hint_info);
    Q_PROPERTY_AUTO(QString, lang_plaza);
    Q_PROPERTY_AUTO(QString, lang_schedule);
    Q_PROPERTY_AUTO(QString, lang_department_evento);
    Q_PROPERTY_AUTO(QString, lang_calendar);
    Q_PROPERTY_AUTO(QString, lang_manage);
    Q_PROPERTY_AUTO(QString, lang_my);
    Q_PROPERTY_AUTO(QString, lang_user_feedback);
    Q_PROPERTY_AUTO(QString, lang_theming);
    Q_PROPERTY_AUTO(QString, lang_dark_mode);

    // Login
    Q_PROPERTY_AUTO(QString, lang_login);
    Q_PROPERTY_AUTO(QString, lang_use_link);
    Q_PROPERTY_AUTO(QString, lang_login_failed);
    Q_PROPERTY_AUTO(QString, lang_by_cpp);
    Q_PROPERTY_AUTO(QString, lang_guest_login);
    Q_PROPERTY_AUTO(QString, lang_Link_login);
    Q_PROPERTY_AUTO(QString, lang_scan_login);
    Q_PROPERTY_AUTO(QString, lang_username_login);
    Q_PROPERTY_AUTO(QString, lang_username);
    Q_PROPERTY_AUTO(QString, lang_password);
    Q_PROPERTY_AUTO(QString, lang_login_hint);

    // plaza
    Q_PROPERTY_AUTO(QString, lang_undertaking_evento);
    Q_PROPERTY_AUTO(QString, lang_latest_evento);

    // schedule
    Q_PROPERTY_AUTO(QString, lang_registered_evento);
    Q_PROPERTY_AUTO(QString, lang_subscribed_evento);
    Q_PROPERTY_AUTO(QString, lang_feedback);
    Q_PROPERTY_AUTO(QString, lang_modify_feedback);
    Q_PROPERTY_AUTO(QString, lang_check_message);
    Q_PROPERTY_AUTO(QString, lang_check_hint);

    // evento info
    Q_PROPERTY_AUTO(QString, lang_undertaking);
    Q_PROPERTY_AUTO(QString, lang_not_started);
    Q_PROPERTY_AUTO(QString, lang_registering);
    Q_PROPERTY_AUTO(QString, lang_over);
    Q_PROPERTY_AUTO(QString, lang_cancelled);
    Q_PROPERTY_AUTO(QString, lang_check_in);
    Q_PROPERTY_AUTO(QString, lang_checked_in);
    Q_PROPERTY_AUTO(QString, lang_subscribe);
    Q_PROPERTY_AUTO(QString, lang_unsubscribe);
    Q_PROPERTY_AUTO(QString, lang_feedback_text);
    Q_PROPERTY_AUTO(QString, lang_feedback_hint);
    Q_PROPERTY_AUTO(QString, lang_modify_and_submit);
    Q_PROPERTY_AUTO(QString, lang_submit);
    Q_PROPERTY_AUTO(QString, lang_submit_success);
    Q_PROPERTY_AUTO(QString, lang_register);
    Q_PROPERTY_AUTO(QString, lang_cancellation);
    Q_PROPERTY_AUTO(QString, lang_register_success);
    Q_PROPERTY_AUTO(QString, lang_subscribe_hint);

    // my page
    Q_PROPERTY_AUTO(QString, lang_history);
    Q_PROPERTY_AUTO(QString, lang_welcome);
    Q_PROPERTY_AUTO(QString, lang_souvenir_card);
    Q_PROPERTY_AUTO(QString, lang_profile);

    // setting
    Q_PROPERTY_AUTO(QString, lang_settings);
    Q_PROPERTY_AUTO(QString, lang_navigation_view_display_mode);
    Q_PROPERTY_AUTO(QString, lang_followSystem);
    Q_PROPERTY_AUTO(QString, lang_light);
    Q_PROPERTY_AUTO(QString, lang_dark);
    Q_PROPERTY_AUTO(QString, lang_locale);
    Q_PROPERTY_AUTO(QString, lang_zh);
    Q_PROPERTY_AUTO(QString, lang_en);
    Q_PROPERTY_AUTO(QString, lang_openSideBar);
    Q_PROPERTY_AUTO(QString, lang_compactSideBar);
    Q_PROPERTY_AUTO(QString, lang_minimalSideBar);
    Q_PROPERTY_AUTO(QString, lang_automatic);
    Q_PROPERTY_AUTO(QString, lang_check_update);
    Q_PROPERTY_AUTO(QString, lang_native_text_rendering);
    Q_PROPERTY_AUTO(QString, lang_animation_effect);
    Q_PROPERTY_AUTO(QString, lang_current_version);
    Q_PROPERTY_AUTO(QString, lang_restart_app_hint);
    Q_PROPERTY_AUTO(QString, lang_software_render_hint);

    // evento block
    Q_PROPERTY_AUTO(QString, lang_copy);
    Q_PROPERTY_AUTO(QString, lang_get_qrcode);
    Q_PROPERTY_AUTO(QString, lang_edit_event);
    Q_PROPERTY_AUTO(QString, lang_cancel_event);
    Q_PROPERTY_AUTO(QString, lang_delete_event);
    Q_PROPERTY_AUTO(QString, lang_confirm_cancel);
    Q_PROPERTY_AUTO(QString, lang_confirm_delete);

    // other
    Q_PROPERTY_AUTO(QString, lang_cancel);
    Q_PROPERTY_AUTO(QString, lang_exit);
    Q_PROPERTY_AUTO(QString, lang_determine_exit);
    Q_PROPERTY_AUTO(QString, lang_ok);
    Q_PROPERTY_AUTO(QString, lang_check_success);
    Q_PROPERTY_AUTO(QString, lang_subscribe_success);
    Q_PROPERTY_AUTO(QString, lang_error);
    Q_PROPERTY_AUTO(QString, lang_input_is_empty);
    Q_PROPERTY_AUTO(QString, lang_check_up_failure);
    Q_PROPERTY_AUTO(QString, lang_reload);
    Q_PROPERTY_AUTO(QString, lang_is_currently_latest_version);
    Q_PROPERTY_AUTO(QString, lang_stay_tuned);
    Q_PROPERTY_AUTO(QString, lang_copy_success);
    Q_PROPERTY_AUTO(QString, lang_move_up);
    Q_PROPERTY_AUTO(QString, lang_move_down);
    Q_PROPERTY_AUTO(QString, lang_loading);
    Q_PROPERTY_AUTO(QString, lang_calendar_hint);

public:
    explicit Lang(QObject* parent = nullptr) {}
};

#endif // LANG_H
