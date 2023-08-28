import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: "Slide Management"

    property int deleteSlideId: 0

    function loadAllSlide(){
        statusMode = FluStatusViewType.Loading
        SlideManagementController.loadAllSlide()
    }

    Connections {
        target: SlideManagementController
        function onLoadAllSlideSuccess() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: SlideManagementController
        function onLoadAllSlideError(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Connections {
        target: SlideManagementController
        function onDeleteSlideSuccess() {
            // TODO 删除成功
        }
    }

    Connections {
        target: SlideManagementController
        function onDeleteSlideError(message) {
            //TODO 删除失败
        }
    }

    Component.onCompleted: {
        loadAllSlide()
    }

    Component {
        id: com_item
        Item {
            Layout.topMargin: 10
            width: listView.width
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
                            source: model.link
                            fillMode: Image.PreserveAspectCrop
                        }
                    }

                    FluText {
                        id: com_title
                        text: model.title
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
                        text: model.link
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
                            deleteSlideId = model.id
                            delete_btn_dialog.open()
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
                            SlideHelper.isEdit = true
                            SlideHelper.id = 1 // TODO 更改id为model.id
                            SlideHelper.title = model.title
                            SlideHelper.link = model.link
                            SlideHelper.url = model.url
                            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml")
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
                            SlideHelper.isEdit = true
                            SlideHelper.id = 1 // TODO 更改id为model.id
                            SlideHelper.title = model.title
                            SlideHelper.link = model.link
                            SlideHelper.url = model.url
                            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml")
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
            SlideHelper.isEdit = false
            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml")
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

    FluContentDialog{
            id:delete_btn_dialog
            title:"删除幻灯片"
            message:"是否确定删除幻灯片？"
            buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
            negativeText:"取消"
            onNegativeClicked:{
                // 取消删除操作
            }
            positiveText:"确定"
            onPositiveClicked:{
                SlideManagementController.deleteSlide(deleteSlideId)
            }
    }
}
