#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    lang_plaza("Evento Plaza");
    lang_schedule("Schedule");
    lang_history("History");
    lang_souvenir_card("Souvenir Card");
    lang_manage("Manage");
    lang_my("My");
    lang_theming("Theming");
    lang_dark_mode("Dark Mode");
    lang_sys_dark_mode("Sync with system");
    lang_search("Search");
    lang_my("My");
    lang_settings("Settings");
    lang_locale("Locale");
    lang_navigation_view_display_mode("NavigationView Display Mode");
    lang_profile("Profile");
    lang_check("Check");

    lang_create_event("Create Event");
    lang_event_info("Event Infomation");
    lang_user_manage("User Management");
    lang_timesheet("Timesheet");
    lang_feedback("Feedback");
    lang_upload_souvenir_card("Upload Souvenir Card");
    lang_slide("Slide");
    lang_others("Others");

    lang_welcome("Welcome Back,");
    lang_login("Login");
    lang_comment("Comment");
    lang_submit("Submuit");
    lang_subscribe("+Subscribe");
    lang_unsubscribe("Unsubscribe");
    lang_checked("Checked");
    lang_undertaking("Undertaking");
    lang_not_started("Not Started");
    lang_over("Over");
    lang_undertaking_evento("Undertaking Evento");
    lang_latest_evento("Latest Evento");
    lang_username("username");
    lang_password("password");
    lang_zh("Chinese");
    lang_en("English");
    lang_participate_in("Participate In");
    lang_cancel("Cancel");
    lang_exit("Exit");
    lang_determine_exit("Determine the exit procedure?");

    lang_followSystem("System");
    lang_light("Light");
    lang_dark("Dark");
    lang_openSideBar("Open");
    lang_compactSideBar("Compact");
    lang_minimalSideBar("Minimal");
    lang_automatical("Auto");
}
