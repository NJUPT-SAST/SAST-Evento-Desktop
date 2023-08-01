import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/global"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    ColumnLayout {
        Layout.topMargin: 10
        Layout.fillWidth: true

        FluText {
            text: "软件研发中心的活动"
            font: FluTextStyle.Title
        }

        FluTextButton {
            text: lang.lang_subscribe
            checked: true
            onClicked: {
                checked = !checked
                if (!checked) {
                    text = lang.lang_unsubscribe
                    showInfo("已订阅")
                    textColor = disableColor
                } else {
                    text = lang.lang_subscribe
                    showInfo("已取消订阅")
                    textColor = pressedColor
                }
            }
        }
        Component {
            id: com_item
            Item {
                Layout.topMargin: 10
                width: 320
                height: 120
                FluArea {
                    radius: 8
                    width: 300
                    height: 100
                    anchors.centerIn: parent
                    Rectangle {
                        anchors.fill: parent
                        radius: 8
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
                    }
                    FluRectangle {
                        id: item_icon
                        height: 80
                        width: 80
                        radius: [6, 6, 6, 6]
                        anchors {
                            left: parent.left
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        FluImage {
                            anchors.fill: parent
                            source: modelData.image
                            fillMode: Image.PreserveAspectCrop
                        }
                    }

                    FluText {
                        id: item_title
                        text: modelData.title
                        font: FluTextStyle.BodyStrong
                        anchors {
                            left: item_icon.right
                            leftMargin: 20
                            top: item_icon.top
                        }
                    }

                    FluText {
                        id: item_desc
                        text: modelData.desc
                        color: FluColors.Grey120
                        wrapMode: Text.WrapAnywhere
                        elide: Text.ElideRight
                        font: FluTextStyle.Caption
                        maximumLineCount: 3
                        anchors {
                            left: item_title.left
                            right: parent.right
                            rightMargin: 20
                            top: item_title.bottom
                            topMargin: 10
                        }
                    }

                    MouseArea {
                        id: item_mouse
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            ItemsOriginal.item.navigationView.push(
                                        "qrc:/SAST_Evento/qml/page/T_EventInfo.qml")
                        }
                    }
                }
            }
        }

        GridView {
            Layout.fillWidth: true
            implicitHeight: contentHeight
            cellHeight: 120
            cellWidth: 320
            interactive: false
            delegate: com_item

            Component.onCompleted: {
                model = getEventItems()
            }
        }
    }

    function getEventItems() {
        var arr = []
        for (var i = 0; i < 10; ++i) {
            arr.push({
                         "image": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                         "title": "活动卡片",
                         "desc": "活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息"
                     })
        }
        return arr
    }
}
