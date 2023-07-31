import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import "qrc:///SAST_Evento/qml/global"
import FluentUI

FluScrollablePage {

    launchMode: FluPageType.SingleTask
    animDisabled: true
    title: lang.home
    FluCarousel {
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.fillWidth: true

        Component.onCompleted: {
            setData([{
                         "url": "qrc:/SAST_Evento/res/image/banner_1.jpg"
                     }, {
                         "url": "qrc:/SAST_Evento/res/image/banner_2.jpg"
                     }, {
                         "url": "qrc:/SAST_Evento/res/image/banner_3.jpg"
                     }])
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
                Image {
                    id: item_icon
                    height: 40
                    width: 40
                    source: modelData.image
                    anchors {
                        left: parent.left
                        leftMargin: 20
                        verticalCenter: parent.verticalCenter
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
                    maximumLineCount: 2
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_title.bottom
                        topMargin: 5
                    }
                }

                Rectangle {
                    height: 12
                    width: 12
                    radius: 6
                    color: FluTheme.primaryColor.dark
                    anchors {
                        right: parent.right
                        top: parent.top
                        rightMargin: 14
                        topMargin: 14
                    }
                }

                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        ItemsOriginal.startPageByItem(modelData)
                    }
                }
            }
        }
    }

    FluText {
        text: "正在进行的活动"
        font: FluTextStyle.Title
        Layout.topMargin: 20
        Layout.leftMargin: 20
    }

    GridView {
        Layout.fillWidth: true
        implicitHeight: contentHeight
        cellHeight: 120
        cellWidth: 320
        interactive: false
        delegate: com_item

        Component.onCompleted: {
            model = ItemsOriginal.getInProgressData()
        }
    }

    FluText {
        text: "最新活动"
        font: FluTextStyle.Title
        Layout.topMargin: 20
        Layout.leftMargin: 20
    }

    GridView {
        Layout.fillWidth: true
        implicitHeight: contentHeight
        cellHeight: 120
        cellWidth: 320
        interactive: false
        delegate: com_item

        Component.onCompleted: {
            model = ItemsOriginal.getRecentlyUpdatedData()
        }
    }
}
