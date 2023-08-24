import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: "Slide Management Edit"

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 520
        paddings: 10
        color: Qt.rgba(0, 0, 0, 0)

        ColumnLayout{
            spacing: 5
            anchors{
                left: parent.left
            }
            RowLayout{
                spacing: 10
                anchors{
                    left: parent.left
                }

                FluText {
                    id: titleText
                    text: "标题"
                    font: FluTextStyle.Body
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluTextBox {
                    id: titleTextbox
                    width: 180
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }
            }

            RowLayout{
                spacing: 10
                anchors{
                    left: parent.left
                }

                FluText {
                    id: linkText
                    text: "链接"
                    font: FluTextStyle.Body
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluTextBox {
                    id: linkTextbox
                    width: 180
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }
            }

            RowLayout{
                spacing: 10
                anchors{
                    left: parent.left
                }

                FluText {
                    id: urlText
                    text: "链接"
                    font: FluTextStyle.Body
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluButton{
                    id: urlButton
                    text: "打开图库"
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }
            }

            FluText {
                id: viewText
                text: "幻灯片预览"
            }

            FluRectangle {
                id: slideView
                height: 330
                width: 800
                radius: [6, 6, 6, 6]
                Layout.leftMargin: 10
                FluImage {
                    anchors.fill: parent
                    source: "qrc:/res/image/banner_3.png"
                    fillMode: Image.PreserveAspectCrop
                }
            }

            Rectangle {
                id: buttonField
                height: 50
                width: 800
                radius: [6, 6, 6, 6]
                Layout.leftMargin: 10
                color: Qt.rgba(0, 0, 0, 0)
                FluButton{
                    id: submitButton
                    text: "提交"
                    anchors.right: parent.right
                    onClicked: {

                    }
                }
            }
        }
    }


}
