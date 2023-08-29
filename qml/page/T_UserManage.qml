import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../imports"
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_user_manage
    Layout.fillWidth: true

    FluIconButton {
        id:btn_add
        iconSource: FluentIcons.Add
        Layout.alignment: Qt.AlignRight

        onClicked: {
            UserManagementController.updateIsEdit(false)
            MainWindow.window.pushPage(
                        "qrc:/qml/page/T_UserPermission.qml")
        }
    }

    Column {
        id: users_col
        width: parent.width
        spacing: 15

        Component {
            id: com_item

            Item {
                Layout.topMargin: 10
                width: parent.width
                height: 80
                FluArea {
                    radius: 8
                    width: parent.width
                    height: 70
                    anchors.centerIn: parent

                    FluText {
                        id: item_id
                        text: modelData.id
                        font: FluTextStyle.Title
                        anchors {
                            left: parent.left
                            top: parent.top
                            leftMargin: 10
                            topMargin: 5
                        }
                    }

                    FluText {
                        id: item_comment
                        text: "权限 " + modelData.permission
                        wrapMode: Text.WordWrap
                        width: parent.width - 20
                        font: FluTextStyle.Body
                        anchors {
                            top: item_id.bottom
                            topMargin: 5
                            left: parent.left
                            leftMargin: 10
                        }
                    }

                    FluIconButton {
                        id: btn_edit
                        iconSource: FluentIcons.Edit
                        anchors {
                            right: item_comment.right
                            bottom: parent.bottom
                            bottomMargin: 5
                        }

                        onClicked: {
                            UserManagementController.updateUserId(modelData.id)
                            UserManagementController.updateIsEdit(true)
                            MainWindow.window.pushPage(
                                        "qrc:/qml/page/T_UserPermission.qml")
                        }
                    }

                    FluIconButton {
                        id: btn_del
                        iconSource: FluentIcons.Delete
                        anchors {
                            right: btn_edit.left
                            top: btn_edit.top
                            rightMargin: 10
                        }

                        onClicked: {
                            //wait to be completed
                            showSuccess("删除成功")
                        }
                    }
                }
            }
        }

        ListView {
            id: listView
            width: parent.width
            implicitHeight: contentHeight
            interactive: false
            delegate: com_item

            Component.onCompleted: {
                model = loadData(1, 10)
            }
        }

        FluPagination {
            id: gagination
            anchors {
                left: parent.left
            }
            width: parent.width
            pageCurrent: 1
            itemCount: 40
            pageButtonCount: 7
            __itemPerPage: 10
            onRequestPage: (page, count) => {
                               listView.model = loadData(page, count)
                           }
        }
    }
    
    // 加载某一页的制定数目用户条数
    function loadData(page, count) {
        const dataSource = []
        for (var i = 0; i < count; i++) {
            if (page === 2) {
                dataSource.push({
                                    "id": "B12345678",
                                    "permission": 1
                                })
            } else
                dataSource.push({
                                    "id": "B12345666",
                                    "permission": 2
                                })
        }
        return dataSource
    }
}
