pragma Singleton

import QtQuick
import FluentUI

FluObject {

    property var navigationView

    FluPaneItem {
        id: item_home
        count: 9
        title: lang.home
        infoBadge: FluBadge {
            count: item_home.count
        }
        icon: FluentIcons.Home
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
        }
    }

    FluPaneItem {
        id: item_schedule
        count: 9
        title: lang.schedule
        infoBadge: FluBadge {
            count: item_schedule.count
        }
        icon: FluentIcons.Calendar
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_schedule.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Schedule.qml")
        }
    }

    FluPaneItemExpander {
        title: lang.organize
        icon: FluentIcons.AllApps
        FluPaneItem {
            title: lang.createEvent
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_TextBox.qml")
            }
        }
        FluPaneItem {
            title: lang.eventInfo
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_InfoBar.qml")
            }
        }
    }

    FluPaneItemExpander {
        title: lang.manage
        icon: FluentIcons.ViewAll
        FluPaneItem {
            title: lang.feedback

            onTap: {
                navigationView.push(
                    "qrc:/SAST_Evento/qml/page/T_RadioButton.qml")
            }
        }
        FluPaneItem {
            title: lang.timesheet
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Progress.qml")
            }
        }
        FluPaneItem {
            title: lang.usermanage
            onTap: {
                navigationView.push(
                    "qrc:/SAST_Evento/qml/page/T_RatingControl.qml")
            }
        }
        FluPaneItem {
            title: lang.uploadSouvenirCard
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Badge.qml")
            }
        }
        FluPaneItem {
            title: lang.ppt
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Rectangle.qml")
            }
        }
    }
}
