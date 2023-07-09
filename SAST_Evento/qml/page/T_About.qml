import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/component"

Rectangle {
    ColumnLayout {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        RowLayout {
            Layout.topMargin: 50
            Layout.leftMargin: 15
            spacing: 14
            FluText {
                text: "SAST Evento"
                font: FluTextStyle.Title
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        FluApp.navigate("/")
                    }
                }
            }
            FluText {
                text: "v%1".arg(appInfo.version)
                font: FluTextStyle.Body
                Layout.alignment: Qt.AlignBottom
            }
        }

        RowLayout {
            Layout.leftMargin: 15
            FluText {
                text: "SAST C++组开发"
                font: FluTextStyle.Body
                Layout.alignment: Qt.AlignBottom
            }
        }
    }
}
