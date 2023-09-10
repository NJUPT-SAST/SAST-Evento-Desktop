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
    property var allStateArr: []
    property var createPermissionArr: []
    property string userId: UserManagementController.getUserId()
    property bool isEdit: UserManagementController.getIsEdit()

    //返回一个用于辅助创建权限列表的数组
    function parseJSON(data) {
        var result = []
        if (Array.isArray(data)) {
            // 是一个数组，存在多个对象的情况
            for (var i = 0; i < data.length; i++) {
                var item = data[i]
                var title = item.title
                var isLeaf = false
                var children = []

                if (item.children && Array.isArray(item.children)) {
                    children = parseJSON(item.children)
                } else {
                    isLeaf = true
                }

                result.push([title, isLeaf, children])
            }
        } else {
            // 只有一个对象的情况
            result.push([title, isLeaf, children])
        }
        return result
    }

    function loadPermissionInfo() {
        statusMode = FluStatusViewType.Loading
        var permission = UserManagementController.loadPermissionInfo()
        permissionArr = JSON.parse(permission)
        createPermissionArr = parseJSON(JSON.parse(permission))
        outer_check_rep.model = createPermissionArr
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
    }

    Item {
        id: item_all
        Layout.fillWidth: true
        height: 560

        Loader {
            id: title_loader
            anchors {
                top: parent.top
            }
            sourceComponent: isEdit ? text1 : editable_text
        }

        Component {
            id: text1
            FluText {
                id: text1Text
                text: userId
                font: FluTextStyle.Title
                anchors {
                    top: parent.top
                }
            }
        }

        Component {
            id: editable_text
            FluTextBox {
                text: '请填写学号'
                width: 150
                height: 40
                anchors {
                    top: parent.top
                }
            }
        }

        FluText {
            id: text2
            text: "用户权限"
            font: FluTextStyle.Body
            anchors {
                top: title_loader.bottom
                topMargin: 10
                leftMargin: 20
            }
        }

        FluArea {
            id: check_area
            width: parent.width
            height: 500 - title_loader.height - text2.height - 20
            anchors {
                top: text2.bottom
                topMargin: 20
                left: parent.left
            }

            FluScrollablePage {
                anchors.fill: parent
                implicitHeight: permission_col.implicitHeight
                ColumnLayout {
                    id: permission_col
                    spacing: 10
                    Repeater {
                        id: outer_check_rep
                        model: createPermissionArr

                        delegate: Item {
                            width: parent.width
                            height: inner_list.implicitHeight + father_check_box.implicitHeight
                            FluCheckBox {
                                id: father_check_box
                                text: modelData[0]
                            }

                            ListView {
                                id: inner_list
                                width: parent.width
                                implicitHeight: contentHeight
                                anchors {
                                    top: father_check_box.bottom
                                    topMargin: 10
                                }
                                spacing: 10
                                model: modelData[2]

                                delegate: FluCheckBox {
                                    id: child_check_box
                                    checked: father_check_box.checked
                                    text: modelData[0]
                                    anchors {
                                        left: parent.left
                                        leftMargin: 30
                                    }
                                    Connections {
                                        target: father_check_box
                                        function onCheckedChanged() {
                                            child_check_box.checked = Qt.binding(
                                                        function () {
                                                            return father_check_box.checked
                                                        })
                                        }
                                    }
                                }
                            }
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
                allStateArr = []

                // 遍历复选框，检查勾选状态，并将文本和勾选状态添加到数组
                for (var i = 0; i < outer_check_rep.count; i++) {
                    var permissionTitle = outer_check_rep.itemAt(i).text
                    var permissionState = outer_check_rep.itemAt(
                                i).checked ? true : false
                    allStateArr.push([permissionTitle, permissionState])
                }

                UserManagementController.createUser(allStateArr)
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
