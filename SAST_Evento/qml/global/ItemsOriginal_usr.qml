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
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
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

    FluPaneItem {
        id: item_theming
        title: lang.theming
        infoBadge: FluBadge {
            count: 0
        }
        icon: FluentIcons.Brightness
        onTap: {
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Theme.qml")
        }
    }
}
