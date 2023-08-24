import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: "Slide Management"

    Component {
        id: com_item
        Item {
            Layout.topMargin: 10
            width: parent.width
            height: 90
            FluArea {
                radius: 8
                width: parent.width
                height: 80
                anchors.centerIn: parent
                Rectangle {
                    anchors.fill: parent
                    radius: 8
                    width: parent.width
                    color: {
                        if (FluTheme.dark) {
                            if (item_mouse.containsMouse) {
                                return Qt.rgba(1, 1, 1, 0.03)
                            }
                            return Qt.rgba(0, 0, 0, 0)
                        } else {
                            if (item_mouse.containsMouse) {
                                return Qt.rgba(0, 0, 0, 0.03)
                            }
                            return Qt.rgba(0, 0, 0, 0)
                        }
                    }
                    FluRectangle {
                        id: item_icon
                        height: parent.height - 20
                        width: 115
                        radius: [6, 6, 6, 6]
                        anchors {
                            left: parent.left
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        FluImage {
                            anchors.fill: parent
                            source: "qrc:/res/image/banner_3.png"
                            fillMode: Image.PreserveAspectCrop
                        }
                    }

                    FluText {
                        id: com_title
                        text: title
                        font: FluTextStyle.Title
                        anchors {
                            left: item_icon.right
                            top: parent.top
                            leftMargin: 10
                            topMargin: 5
                        }
                    }

                    FluText {
                        id: com_link
                        text: link
                        font: FluTextStyle.Body
                        anchors {
                            top: com_title.bottom
                            topMargin: 5
                            left: item_icon.right
                            leftMargin: 10
                        }
                    }

                    FluIconButton {
                        id: deleteButton
                        iconSource: FluentIcons.Delete
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: parent.right
                            rightMargin: 10
                        }

                        onClicked: {

                        }
                    }

                    FluIconButton {
                        id: editButton
                        iconSource: FluentIcons.Edit
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: deleteButton.left
                            rightMargin: 10
                        }

                        onClicked: {

                        }
                    }

                    MouseArea {
                        id: item_mouse
                        anchors {
                            fill: parent
                            rightMargin: 80
                        }

                        hoverEnabled: true
                        onClicked: {

                        }
                    }
                }
            }
        }
    }

    FluIconButton {
        id: addButton
        iconSource: FluentIcons.Add
        Layout.alignment: Qt.AlignRight
        onClicked: {

        }
    }

    ListView {
        id: listView
        model: SlideModel
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        delegate: com_item
    }
}
