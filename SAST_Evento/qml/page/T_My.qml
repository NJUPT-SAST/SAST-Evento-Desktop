import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/component"

FluScrollablePage {
    title: lang.my

    property var loginPageRegister: registerForWindowResult("/login")

    Connections {
        target: loginPageRegister
        function onResult(data) {
            if (data.ok) {
                appInfo.changeIdentity(data.username, data.password)
                //MainWindow.window.showSuccess("登录成功")
            } else {
                status.text = "未登录"
                loader.sourceComponent = noLogin
                //MainWindow.window.showInfo("未登录，请前往“我的”以登录账号")
            }
        }
    }

    Component.onCompleted: {
        if (appInfo.identity.authority === 0) {
            status.text = "未登录"
            loader.sourceComponent = noLogin
            return
        }
        status.text = "账号 " + appInfo.identity.username
        loader.sourceComponent = login
        if (appInfo.identity.authority === 2)
            loader.item.text = "管理员"
        if (appInfo.identity.authority === 1)
            loader.item.text = "普通用户"
    }

    Connections {
        target: appInfo
        function onLogin() {
            if (appInfo.identity.authority === 0) {
                status.text = "未登录"
                loader.sourceComponent = noLogin
                return
            }
            status.text = "账号 " + appInfo.identity.username
            loader.sourceComponent = login
            if (appInfo.identity.authority === 2)
                loader.item.text = "管理员"
            if (appInfo.identity.authority === 1)
                loader.item.text = "普通用户"
        }
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 85
        paddings: 10

        FluText {
            id: status
            text: "未登录"
            font: FluTextStyle.Title
            anchors.top: parent.top
        }
        Loader {
            id: loader
            anchors.bottom: parent.bottom
            sourceComponent: noLogin
        }

        Component {
            id: login
            FluText {
                text: ""
                font: FluTextStyle.Body
            }
        }

        Component {
            id: noLogin
            FluButton {
                id: button
                text: "登录"
                anchors.right: parent.right

                onClicked: {
                    loginPageRegister.launch({
                                                 "username": "admin"
                                             })
                }
            }
        }
    }
}
