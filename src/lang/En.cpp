#include "En.h"

En::En(QObject* parent) : Lang{parent} {
    setObjectName("En");

    // MainWindow
    lang_hint("HINT");
    lang_hint_info(
        "SAST Evento has been hidden to the tray. Click the tray to activate the window again.");
    lang_plaza("Evento Plaza");
    lang_schedule("Schedule");
    lang_department_evento("Department Evento");
    lang_calendar("Calendar");
    lang_manage("Manage");
    lang_my("My");
    lang_user_feedback("User Feedback");
    lang_theming("Theming");
    lang_dark_mode("Dark Mode");

    // Login
    lang_login("Login");
    lang_use_link("       Login by Link");
    lang_login_failed("Login Failed");
    lang_by_cpp("Developed by SAST-C++ Group\n");
    lang_visitor_login("Visitor Login");

    // Plaza
    lang_undertaking_evento("Undertaking Evento");
    lang_latest_evento("Latest Evento");

    // schedule
    lang_registered_evento("Registered");
    lang_subscribed_evento("Subscribed");
    lang_feedback("Feedback");
    lang_modify_feedback("modify feedback");
    lang_check_message("Use WeChat Mini Program to scan the QR code or enter a key.");
    lang_check_hint("Please get the key from the instructor");

    // event info
    lang_undertaking("Undertaking");
    lang_not_started("Not Started");
    lang_over("Over");
    lang_cancelled("Cancelled");
    lang_checked_in("Checked");
    lang_check_in("Check in");
    lang_subscribe("+Subscribe");
    lang_unsubscribe("Unsubscribe");
    lang_feedback_text("Score the event and your feedback will be uploaded anonymously.");
    lang_feedback_hint("Enter your message (optional, Ctrl + Enter Newline)");
    lang_modify_and_submit("Modify");
    lang_submit("Submit");
    lang_submit_success("Submit Succeed");
    lang_register("Register");
    lang_cancellation("Cancellation");
    lang_register_success("Register Succeed");
    lang_subscribe_hint(
        "After you subscribe, WeChat Mini Program\nwill notify you before the event starts");

    // my page
    lang_history("History");
    lang_welcome("Welcome Back, ");
    lang_souvenir_card("Souvenir Card");
    lang_profile("Profile");

    // setting
    lang_settings("Settings");
    lang_navigation_view_display_mode("NavigationView Display Mode");
    lang_followSystem("System");
    lang_light("Light");
    lang_dark("Dark");
    lang_locale("Locale");
    lang_zh("Chinese");
    lang_en("English");
    lang_openSideBar("Open");
    lang_compactSideBar("Compact");
    lang_minimalSideBar("Minimal");
    lang_automatical("Auto");
    lang_check_update("Check Update");
    lang_native_text_rendering("Native Text Rendering");
    lang_animation_effect("Animation Effect");

    // other
    lang_cancel("Cancel");
    lang_exit("Exit");
    lang_determine_exit("Determine the exit procedure?");
    lang_ok("OK");
    lang_check_success("Check in Succeed");
    lang_subscribe_success("Subscribe Succeed");
    lang_error("error: ");
    lang_input_is_empty("Input is empty");
    lang_check_up_failure("Check up failure: ");
    lang_reload("Reload");
    lang_is_currently_latest_version("Already the latest version!");
    lang_stay_tuned("STAY TUNED");
    lang_copy_success("Copy Success");
    lang_move_up("Move one layer up");
    lang_move_down("Move one layer down");
    lang_loading("Loading...");
    lang_calendar_hint("Adjustable layer by right-clicking event card");
}
