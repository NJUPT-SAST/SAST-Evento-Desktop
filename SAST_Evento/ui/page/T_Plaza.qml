import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import "qrc:///SAST_Evento/ui/global"
import FluentUI

FluScrollablePage {

    launchMode: FluPageType.SingleTask
    animDisabled: true
    title: lang.lang_plaza

    ListModel {
        id: data_model
        ListElement {
            url: "qrc:/example/res/image/banner_1.jpg"
            title: "qqq"
        }
        ListElement {
            url: "qrc:/example/res/image/banner_2.jpg"
            title: "qqq"
        }
        ListElement {
            url: "qrc:/example/res/image/banner_3.jpg"
            title: "qqq"
        }
    }

    FluCarousel {
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.fillWidth: true
        radius: [15, 15, 15, 15]
        loopTime: 1500
        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
        indicatorMarginTop: 15
        model: data_model
        delegate: Component {
            Item {
                anchors.fill: parent
                Image {
                    anchors.fill: parent
                    source: modelData.url
                    asynchronous: true
                    fillMode: Image.PreserveAspectCrop
                }
                Rectangle {
                    height: 40
                    width: parent.width
                    anchors.bottom: parent.bottom
                    color: "#33000000"
                    FluText {
                        anchors.fill: parent
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        text: modelData.title
                        color: FluColors.Grey10
                        font.pixelSize: 15
                    }
                }
            }
        }
    }

    FluCarousel {

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
                    wrapMode: Text.WordWrap
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
                        ItemsOriginal.item.navigationView.push(
                                    "qrc:/SAST_Evento/qml/page/T_EventInfo.qml")
                    }
                }
            }
        }
    }

    FluText {
        text: lang.lang_undertaking_evento
        font: FluTextStyle.Title
        Layout.topMargin: 20
        Layout.leftMargin: 20
    }

    Component {
        id: com_item1
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
                    wrapMode: Text.WordWrap
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
        delegate: com_item1

        Component.onCompleted: {
            model = getEventItems()
        }
    }

    FluText {
        text: lang.lang_latest_evento
        font: FluTextStyle.Title
        Layout.topMargin: 20
        Layout.leftMargin: 20
    }

    Component {
        id: com_item2
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
                    wrapMode: Text.WordWrap
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
        delegate: com_item2

        Component.onCompleted: {
            model = getEventItems()
        }
    }

    function getEventItems() {
        var arr = []
        for (var i = 0; i < 3; ++i) {
            arr.push({
                         "image": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                         "title": "活动卡片",
                         "desc": "活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息"
                     })
        }
        return arr
    }
}
