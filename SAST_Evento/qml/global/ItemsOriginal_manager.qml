pragma Singleton

import QtQuick
import FluentUI

FluObject {

    property var navigationView

    FluPaneItem {
        id: item_home
        count: 9
        title: lang.lang_plaza
        infoBadge: FluBadge {
            count: item_home.count
        }
        icon: FluentIcons.Home
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Plaza.qml")
        }
    }

    FluPaneItem {
        id: item_schedule
        count: 9
        title: lang.lang_schedule
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
        title: lang.lang_manage
        icon: FluentIcons.AllApps
        FluPaneItem {
            title: lang.lang_timesheet
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Timesheet.qml")
            }
        }
        FluPaneItem {
            title: lang.lang_feedback
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Feedback.qml")
            }
        }
    }

    FluPaneItemExpander {
        title: lang.lang_others
        icon: FluentIcons.ViewAll
        FluPaneItem {
            title: lang.lang_user_manage
            onTap: {
                navigationView.push(
                    "qrc:/SAST_Evento/qml/page/T_UserManage.qml")
            }
        }
        FluPaneItem {
            title: lang.lang_upload_souvenir_card
            onTap: {
                navigationView.push(
                    "qrc:/SAST_Evento/qml/page/T_SouvenirCard.qml")
            }
        }
        FluPaneItem {
            title: lang.lang_slide
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Slide.qml")
            }
        }
    }
}
