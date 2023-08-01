#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    lang_home("Events Square");
    lang_schedule("Schedule");
    lang_history("History");
    lang_souvenirCard("Souvenir Card");
    lang_organize("Organize");
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
    lang_personalData("Personal Data");
    lang_sign_in("Sign In");

    lang_createEvent("Create Event");
    lang_eventInfo("Event Infomation");
    lang_usermanage("User Management");
    lang_timesheet("Timesheet");
    lang_feedback("Feedback");
    lang_uploadSouvenirCard("Upload Souvenir Card");
    lang_ppt("PowerPoint");

    lang_welcome("Welcome Back,");
    lang_login("Login");
    lang_comment("Comment");
    lang_publish("Publish");
    lang_subscribe("+Subscribe");
    lang_unsubscribe("Unsubscribe");
    lang_signed_in("Signed In");
    lang_in_progress("Ongoing");
    lang_not_started("Not Started");
    lang_over("Over");
    lang_ongoing_events("Ongoing Events");
    lang_latest_events("Latest Events");
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
