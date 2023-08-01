import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/global"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.my

    Settings {
        id: settings
        property string username
    }

    property var loginPageRegister: registerForWindowResult("/login")

    Connections {
        target: loginPageRegister
        function onResult(data) {
            if (data.ok) {
                appInfo.changeIdentity(data.username, data.password)
                settings.username = data.username
            } else {
                loader.sourceComponent = noLogin
            }
        }
    }

    Component.onCompleted: {
        if (appInfo.identity.authority === 0) {
            loader.sourceComponent = noLogin
            return
        }
        loader.sourceComponent = login
    }

    Connections {
        target: appInfo
        function onLogin() {
            if (appInfo.identity.authority === 0) {
                loader.sourceComponent = noLogin
                return
            }
            loader.sourceComponent = login
            if (appInfo.identity.authority === 2)
                loader.item.text = "管理员"
            if (appInfo.identity.authority === 1)
                loader.item.text = "普通用户"
        }
    }

    Loader {
        id: loader
        sourceComponent: noLogin
        Layout.fillWidth: true
    }

    Component {
        id: noLogin

        FluArea {
            Layout.fillWidth: true
            Layout.topMargin: 50
            height: 85
            paddings: 10
            FluTextButton {
                id: button
                text: "登录"

                onClicked: {
                    loginPageRegister.launch({
                                                 "username": settings.value(
                                                                 "username", "")
                                             })
                }
            }
        }
    }

    Component {
        id: login

        ColumnLayout {
            Layout.fillWidth: true

            FluArea {
                Layout.fillWidth: true
                Layout.topMargin: 20
                height: 70
                paddings: 10
                border.width: 0
                color: "transparent"
                FluRectangle {
                    id: img
                    width: 70
                    height: 70
                    radius: [35, 35, 35, 35]
                    Image {
                        asynchronous: true
                        anchors.fill: parent
                        sourceSize: Qt.size(width, height)
                        source: "qrc:/SAST_Evento/res/svg/avatar_3.svg"
                    }
                }
                Column {
                    anchors.left: img.right
                    anchors.leftMargin: 15
                    FluText {
                        text: "欢迎回来，"
                        font: FluTextStyle.Title
                    }
                    FluText {
                        text: appInfo.identity.username
                        font: FluTextStyle.Subtitle
                    }
                }
            }

            FluArea {
                Layout.fillWidth: true
                Layout.topMargin: 10
                height: 110
                paddings: 20
                border.width: 0
                color: "transparent"

                Column {
                    id: button_signIn
                    anchors.leftMargin: 50
                    FluIconButton {
                        width: 50
                        height: 50
                        scale: 1.8
                        iconSource: FluentIcons.Trackers
                    }
                    FluText {
                        text: "签到"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Column {
                    id: button_souvenirCard
                    anchors {
                        left: button_signIn.right
                        leftMargin: parent.width / 3
                    }

                    FluIconButton {
                        width: 50
                        height: 50
                        scale: 1.8
                        iconSource: FluentIcons.Smartcard

                        onClicked: {
                            ItemsOriginal.item.navigationView.push(
                                        "qrc:/SAST_Evento/qml/page/T_SouvenirCard.qml")
                        }
                    }
                    FluText {
                        text: "纪念卡"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Column {
                    anchors {
                        left: button_souvenirCard.right
                        leftMargin: parent.width / 3
                    }

                    FluIconButton {
                        width: 50
                        height: 50
                        scale: 1.8
                        iconSource: FluentIcons.PersonalFolder
                    }
                    FluText {
                        text: "个人资料"
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }

            FluText {
                text: "历史活动"
                font: FluTextStyle.Subtitle
                Layout.leftMargin: 20
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
