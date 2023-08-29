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
    property bool isEdit : UserManagementController.getIsEdit()

    function loadPermissionInfo() {
        statusMode = FluStatusViewType.Loading
        var permission = UserManagementController.loadPermissionInfo()
        permissionArr = JSON.parse(permission)
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
        height: 560

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
            id: check_area
            width: parent.width
            height: 500 - text1.height - text2.height - 20
            anchors {
                top: text2.bottom
                topMargin: 20
                left: parent.left
            }

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

        FluFilledButton {
            id: btn_ok
            anchors {
                top: check_area.bottom
                topMargin: 20
                right: check_area.right
                rightMargin: 10
            }
            disabled: false
            text: "确定"

            onClicked: {
                statusMode = FluStatusViewType.Loading
                arr = []

                // 遍历复选框，检查勾选状态，并将文本和勾选状态添加到数组
                for (var i = 0; i < left_check_rep.count; i++) {
                    var permissionTitle = left_check_rep.itemAt(i).text
                    var permissionState = left_check_rep.itemAt(i).checked ? true : false;
                    arr.push([permissionTitle,permissionState])
                }

                UserManagementController.createUser(arr)
            }
        }

        FluButton {
            id: btn_cancel
            anchors {
                top: btn_ok.top
                right: btn_ok.left
                rightMargin: 20
            }
            disabled: false
            text: "取消"

            onClicked: {
                statusMode = FluStatusViewType.Loading
                returnPage()
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
