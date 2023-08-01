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
}
