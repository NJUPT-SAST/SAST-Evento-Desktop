import "../component"
import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollableStatusPage {
    id: slidePage

    property int deleteSlideId: 0

    function loadAllSlide() {
        statusMode = FluStatusLayoutType.Loading;
        SlideManagementController.loadAllSlide();
    }

    function deleteSlide() {
        statusMode = FluStatusLayoutType.Loading;
        SlideManagementController.deleteSlide(deleteSlideId);
    }

    launchMode: FluPageType.SingleTask
    title: "Slide Management"
    Component.onCompleted: {
        loadAllSlide();
    }

    Connections {
        function onLoadAllSlideSuccess() {
            statusMode = FluStatusLayoutType.Success;
        }

        target: SlideManagementController
    }

    Connections {
        function onLoadAllSlideError(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: SlideManagementController
    }

    Connections {
        function onDeleteSlideSuccess() {
            statusMode = FluStatusLayoutType.Success;
            showSuccess("删除幻灯片成功");
        }

        target: SlideManagementController
    }

    Connections {
        function onDeleteSlideError(message) {
            statusMode = FluStatusLayoutType.Success;
            showError("删除失败(错误信息: " + message + ")");
        }

        target: SlideManagementController
    }

    Component {
        id: com_item

        Item {
            Layout.topMargin: 10
            width: listView.width
            height: 90

            FluFrame {
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
                            if (item_mouse.containsMouse)
                                return Qt.rgba(1, 1, 1, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        } else {
                            if (item_mouse.containsMouse)
                                return Qt.rgba(0, 0, 0, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
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
                        width: slidePage.width - slidePage.rightPadding - slidePage.leftPadding - anchors.leftMargin - editButton.width - editButton.anchors.rightMargin - deleteButton.width - deleteButton.anchors.rightMargin - item_icon.width - item_icon.anchors.leftMargin
                        elide: Text.ElideRight
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
                        onClicked: {
                            deleteSlideId = model.id;
                            delete_btn_dialog.open();
                        }

                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: parent.right
                            rightMargin: 10
                        }

                    }

                    FluIconButton {
                        id: editButton

                        iconSource: FluentIcons.Edit
                        onClicked: {
                            SlideHelper.isEdit = true;
                            SlideHelper.id = model.id;
                            SlideHelper.title = model.title;
                            SlideHelper.link = model.link;
                            SlideHelper.url = model.url;
                            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml");
                        }

                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: deleteButton.left
                            rightMargin: 10
                        }

                    }

                    MouseArea {
                        id: item_mouse

                        hoverEnabled: true
                        onClicked: {
                            SlideHelper.isEdit = true;
                            SlideHelper.id = model.id;
                            SlideHelper.title = model.title;
                            SlideHelper.link = model.link;
                            SlideHelper.url = model.url;
                            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml");
                        }

                        anchors {
                            fill: parent
                            rightMargin: 80
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
            SlideHelper.isEdit = false;
            MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml");
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

    FluContentDialog {
        // 取消删除操作

        id: delete_btn_dialog

        title: "删除幻灯片"
        message: "是否确定删除幻灯片？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        onNegativeClicked: {
        }
        positiveText: "确定"
        onPositiveClicked: {
            deleteSlide();
        }
    }

}
