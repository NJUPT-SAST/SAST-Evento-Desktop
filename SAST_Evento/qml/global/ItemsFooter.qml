pragma Singleton

import QtQuick
import FluentUI

FluObject {

    property var navigationView

    id: footer_items

    FluPaneItemSeparator {}

    FluPaneItem {
        title: lang.my
        icon: FluentIcons.Contact
        onTap: {
            navigationView.push("qrc:/SAST_Evento/qml/page/T_My.qml")
        }
    }

    FluPaneItem {
        title: lang.settings
        icon: FluentIcons.Settings
        onTap: {
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Settings.qml")
        }
    }
}
