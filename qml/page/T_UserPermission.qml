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

    function parseJSON(data) {
        var result = []
        if (Array.isArray(data)) {
            for (var i = 0; i < data.length; i++) {
                var item = data[i]
                var title = item.title
                var isLeaf = false
                var children = []

                if (item.children && Array.isArray(item.children))
                    children = parseJSON(item.children)
                else
                    isLeaf = true
            }
            result.push(tree_view_permission.createItem(title, isLeaf, children, {
                                                          "id": item.id
                                                      }))
        } else {
            result.push(tree_view_permission.createItem(data.title, true, [], {
                                                          "id": data.id
                                                      }))
        }
        return result
    }

    function loadPermissionInfo() {
        statusMode = FluStatusViewType.Loading
        UserManagementController.loadAllUserInfo();
    }

    Connections {
            target: UserManagementController
            function onLoadAllUserSuccess() {
                console.log(PermissionHelper.permissionJson)
                var json =JSON.parse(PermissionHelper.permissionJson)
                permissionArr = parseJSON(json)
                tree_view_permission.updateData(permissionArr)
                statusMode = FluStatusViewType.Success
            }
        }

//    signal listReady

    Component.onCompleted: {
//        statusMode = FluStatusViewType.Loading
//        console.log("start loading list!")
        loadPermissionInfo()
    }

    FluTreeView {
        id: tree_view_permission
        width: 200
        height: 200
        selectionMode: FluTreeViewType.Multiple
    }

//    Item {
//        id:item_all
//        Layout.fillWidth: true
//        implicitHeight: parent.width

//        FluText {
//            id: text1
//            text: "学号：" + "B22080222"
//            font.pixelSize: 22
//            anchors {
//                top: parent.top
//            }
//        }

//        FluText {
//            id:text2
//            text: "用户权限"
//            font.pixelSize: 22
//            anchors {
//                top: text1.bottom
//                topMargin: 10
//                leftMargin: 20
//            }
//        }

//        FluArea {
//            id: left_check_area
//            width: 300
//            height: parent.height
//            anchors {
//                top: text2.bottom
//                topMargin: 20
//                left: parent.left
//            }
//            FluTreeView {
//                id: tree_view_permission
//                width: 200
//                height: 200
//                selectionMode: FluTreeViewType.Multiple

//            }
//        }

//    }




}
