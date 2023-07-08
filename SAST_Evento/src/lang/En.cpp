#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    home("Home");
    timeTable("Time Table");
    history("History");
    souvenirCard("Souvenir Card");
    organize("Organize");
    manage("Manage");
    my("My");
    theming("Theming");
    dark_mode("Dark Mode");
    sys_dark_mode("Sync with system");
    search("Search");
    my("My");
    settings("Settings");
    locale("Locale");
    navigation_view_display_mode("NavigationView Display Mode");

    zh("Chinese");
    en("English");
}
