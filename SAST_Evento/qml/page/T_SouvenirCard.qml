import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import FluentUI
import "qrc:///SAST_Evento/qml/component"

FluScrollablePage {
    title: lang.souvenirCard
    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 10
        height: 380
        paddings: 10

        FluStatusView {
            anchors.fill: parent
            statusMode: FluStatusViewType.Empty
            Rectangle {
                anchors.fill: parent
                color: FluTheme.primaryColor.dark
            }
        }
    }
}
