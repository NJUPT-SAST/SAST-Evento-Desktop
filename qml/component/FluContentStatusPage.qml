import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FluPage {
    id: control

    default property alias content: container.data
    property alias color: status_view.color
    property alias statusMode: status_view.statusMode
    property alias loadingText: status_view.loadingText
    property alias emptyText: status_view.emptyText
    property alias errorText: status_view.errorText
    property alias errorButtonText: status_view.errorButtonText
    property alias loadingItem: status_view.loadingItem
    property alias emptyItem: status_view.emptyItem
    property alias errorItem: status_view.errorItem

    signal errorClicked()

    FluStatusLayout {
        id: status_view

        color: "#00000000"
        statusMode: FluStatusLayoutType.Success
        onErrorClicked: control.errorClicked()

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            leftMargin: control.leftPadding
            rightMargin: control.rightPadding
            bottomMargin: control.bottomPadding
        }

        Item {
            id: container

            clip: true
            anchors.fill: parent
        }

    }

}
