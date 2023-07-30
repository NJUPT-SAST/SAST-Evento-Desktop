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
        id: item_timesheet
        count: 9
        title: lang.timesheet
        infoBadge: FluBadge {
            count: item_timesheet.count
        }
        icon: FluentIcons.Calendar
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_timesheet.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_FlipView.qml")
        }
    }

    FluPaneItem {
        id: item_history
        count: 0
        title: lang.history
        infoBadge: FluBadge {
            count: item_history.count
        }
        icon: FluentIcons.Replay
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_history.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
        }
    }

    FluPaneItem {
        id: item_souvenirCard
        count: 0
        title: lang.souvenirCard
        infoBadge: FluBadge {
            count: item_souvenirCard.count
        }
        icon: FluentIcons.Smartcard
        onTap: {
            if (navigationView.getCurrentUrl()) {
                item_souvenirCard.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_SouvenirCard.qml")
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
            title: lang.addTypes
            image: "qrc:/SAST_Evento/res/image/control/InfoBar.png"
            recentlyUpdated: true
            desc: "An inline message to display app-wide statuschange information."
            onTap: {
                navigationView.push(
                    "qrc:/SAST_Evento/qml/page/T_RadioButton.qml")
            }
        }
        FluPaneItem {
            title: lang.addGroup
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Progress.qml")
            }
        }
        FluPaneItem {
            title: lang.statistics
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
            title: lang.exportTimesheetPictures
            onTap: {
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Rectangle.qml")
            }
        }
    }
}
