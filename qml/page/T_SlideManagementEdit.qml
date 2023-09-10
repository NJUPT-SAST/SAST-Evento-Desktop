import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    function loadSlideInfo() {
        statusMode = FluStatusViewType.Loading
        SlideManagementEditController.loadEditInfo(SlideHelper.id,
                                                   SlideHelper.isEdit)
    }

    function returnPage() {
        MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagement.qml")
    }

    Connections {
        target: SlideManagementEditController
        function onLoadEditSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: SlideManagementEditController
        function onLoadEditErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Connections {
        target: SlideManagementEditController
        function onCreateSuccessEvent() {
            showSuccess("创建幻灯片成功")
            returnPage()
        }
    }

    Connections {
        target: SlideManagementEditController
        function onCreateErrorEvent(message) {
            showError("创建失败(错误信息: " + message + ")")
        }
    }

    Connections {
        target: SlideManagementEditController
        function onUpdateSuccessEvent() {
            showSuccess("更改幻灯片成功")
            returnPage()
        }
    }

    Connections {
        target: SlideManagementEditController
        function onUpdateErrorEvent(message) {
            showError("更改失败(错误信息: " + message + ")")
        }
    }

    Component.onCompleted: {
        statusMode = FluStatusViewType.Loading
        loadSlideInfo()
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 520
        paddings: 10
        color: Qt.rgba(0, 0, 0, 0)

        ColumnLayout {
            spacing: 5
            anchors {
                left: parent.left
            }
            RowLayout {
                spacing: 9
                Layout.leftMargin: 0

                FluText {
                    id: titleText
                    text: "title"
                    font: FluTextStyle.BodyStrong
                    width: 50
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluTextBox {
                    id: titleTextbox
                    implicitWidth: 750
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                    text: SlideHelper.title
                }
            }

            RowLayout {
                spacing: 10
                Layout.leftMargin: 0

                FluText {
                    id: linkText
                    text: "link"
                    font: FluTextStyle.BodyStrong
                    width: 50
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluTextBox {
                    id: linkTextbox
                    implicitWidth: 750
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                    text: SlideHelper.link
                }
            }

            RowLayout {
                spacing: 15
                Layout.leftMargin: 0

                FluText {
                    id: urlText
                    text: "url"
                    font: FluTextStyle.BodyStrong
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                }

                FluFilledButton {
                    id: urlButton
                    text: "打开图库"
                    Layout.topMargin: 1
                    Layout.bottomMargin: 1
                    onClicked: {
                        GalleryHelper.maxNum = 1
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_PictureSelection.qml")
                    }
                }
            }

            FluText {
                id: viewText
                text: "幻灯片预览"
                Layout.leftMargin: 10
                font: FluTextStyle.BodyStrong
            }

            FluRectangle {
                id: slideView
                height: 330
                width: 800
                radius: [6, 6, 6, 6]
                Layout.leftMargin: 10
                FluImage {
                    id: img
                    anchors.fill: parent
                    source: SlideHelper.url
                    fillMode: Image.PreserveAspectCrop
                }
                Connections {
                    target: GalleryHelper
                    function onUrlListChanged() {
                        var arr = GalleryHelper.urlList
                        if (arr.length !== 0)
                            SlideHelper.url = arr[0]
                        else
                            SlideHelper.url = ""
                    }
                }
            }

            Rectangle {
                id: buttonField
                height: 50
                width: 800
                radius: [6, 6, 6, 6]
                Layout.leftMargin: 10
                color: Qt.rgba(0, 0, 0, 0)
                FluFilledButton {
                    id: submitButton
                    text: "提交"
                    anchors {
                        rightMargin: 10
                        right: parent.right
                    }
                    onClicked: {
                        if (titleTextbox.text === "" || linkTextbox.text === ""
                                || SlideHelper.url === "") {
                            showInfo("有信息未填写")
                            return
                        }
                        statusMode = FluStatusViewType.Loading

                        SlideManagementEditController.onClickSubmit(
                                    titleTextbox.text, linkTextbox.text,
                                    SlideHelper.url, SlideHelper.isEdit)
                    }
                }
                FluButton {
                    id: cancelButton
                    text: "取消"
                    anchors {
                        right: submitButton.left
                        rightMargin: 10
                    }

                    onClicked: {
                        returnPage()
                    }
                }
            }
        }
    }
}
