#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    home("Events Square");
    timesheet("Timesheet");
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

    createEvent("Create Event");
    eventInfo("Event Infomation");
    addTypes("Add Event Type");
    addGroup("Add Group");
    statistics("Statistics");
    uploadSouvenirCard("Upload Souvenir Card");
    exportTimesheetPictures("Export Timesheet Pictures");

    zh("Chinese");
    en("English");

    followSystem("System");
    light("Light");
    dark("Dark");
    openSideBar("Open");
    compactSideBar("Compact");
    minimalSideBar("Minimal");
    automatical("Auto");
}
