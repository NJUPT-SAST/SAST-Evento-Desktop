import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtCore
import FluentUI
import SAST_Evento
import "../imports"
import "../window"

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask
    property var permissionArr: []
    property var arr: []
    property string userId : UserManagementController.getUserId()

    function loadPermissionInfo() {
        statusMode = FluStatusViewType.Loading
        var permission = UserManagementController.loadPermissionInfo()
        permissionArr = JSON.parse(permission)
//        tree_view_permission.updateData(permissionArr)
        console.log(permissionArr[1])
    }

    Connections {
        target: UserManagementController
        function onLoadPermissionSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: UserManagementController
        function onLoadPermissionErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Component.onCompleted: {
        loadPermissionInfo()
        text1.text = userId
    }

    Item {
        id: item_all
        Layout.fillWidth: true
        height: 500

        FluText {
            id: text1
            text: "default"
            font: FluTextStyle.Title
            anchors {
                top: parent.top
            }
        }

        FluText {
            id: text2
            text: "用户权限"
            font: FluTextStyle.Body
            anchors {
                top: text1.bottom
                topMargin: 10
                leftMargin: 20
            }
        }

        FluArea {
            id: left_check_area
            width: parent.width
            height: 500
            anchors {
                top: text2.bottom
                topMargin: 20
                left: parent.left
            }

//            FluTreeView {
//                id: tree_view_permission
//                anchors.fill: parent
//                selectionMode: FluTreeViewType.Multiple
//            }

            FluScrollablePage {
                anchors.fill: parent
                implicitHeight: left_col.implicitHeight
                ColumnLayout {
                    id: left_col
                    spacing: 10
                    Repeater {
                        id: left_check_rep
                        model: permissionArr
                        FluCheckBox {
                            text:modelData["title"]
                        }
                    }
                }
            }
        }

//        FluArea {
//            id: right_area
//            width: parent.width - 315
//            height: 500
//            anchors {
//                left: left_check_area.right
//                top: left_check_area.top
//                leftMargin: 15
//            }
//            FluScrollablePage {
//                anchors.fill: parent
//                implicitHeight: col.implicitHeight
//                ColumnLayout {
//                    id: col
//                    spacing: 5
//                    Repeater {
//                        id: rep
//                        FluText {
//                            font.pixelSize: 18
//                            text: modelData
//                        }
//                    }
//                }
//            }
//        }

//        FluFilledButton {
//            anchors {
//                bottom: parent.bottom
//                left: parent.left
//                leftMargin: 240
//                bottomMargin: 5
//            }
//            text: "载入"
//            onClicked: {
//                arr = []
//                tree_view_permission.multipData().map(value => {
//                                                          arr.push(value.text)
//                                                      })
//                rep.model = arr
//                btn_ok.disabled = arr.length === 0
//            }
//        }

        FluFilledButton {
            id: btn_ok
            anchors {
                bottom: parent.bottom
                right: parent.right
                rightMargin: 10
                bottomMargin: 5
            }
            disabled: true
            text: "确定"

            onClicked: {
                statusMode = FluStatusViewType.Loading
                UserManagementController.createUser(arr)
            }
        }
    }

    Connections {
        target: UserManagementController
        function onCreateSuccessEvent() {
            showSuccess("操作成功")
            statusMode = FluStatusViewType.Success
            returnPage()
        }
    }

    Connections {
        target: UserManagementController
        function onCreateErrorEvent(message) {
            showError("错误：" + message)
            statusMode = FluStatusViewType.Success
        }
    }

    function returnPage() {
        MainWindow.window.pushPage("qrc:/qml/page/T_UserManage.qml")
    }
}
