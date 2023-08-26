import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtCore
import FluentUI

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    Item {
        id:item_all
        Layout.fillWidth: true
        implicitHeight: parent.width

        FluText {
            id: text1
            text: "学号：" + "B22080222"
            font.pixelSize: 22
            anchors {
                top: parent.top
            }
        }

        FluText {
            id:text2
            text: "用户权限"
            font.pixelSize: 22
            anchors {
                top: text1.bottom
                topMargin: 10
                leftMargin: 20
            }
        }

        FluArea {
            id: left_check_area
            width: 300
            height: parent.height
            anchors {
                top: text2.bottom
                topMargin: 20
                left: parent.left
            }
            FluTreeView {
                id: tree_view_location
                width: 200
                height: 200
                selectionMode: FluTreeViewType.Multiple
            }
        }

    }




}
