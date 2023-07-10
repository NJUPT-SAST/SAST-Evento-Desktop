import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/component"
import "../window"

FluScrollablePage {

    title: lang.my

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 85
        paddings: 10

        FluText {
            id: status
            text: "未登录"
            //text: MainWindow.username === "" ? "未登录" : "账号 " + MainWindow.username
            font: FluTextStyle.Title
            anchors.top: parent.top
        }
        Loader {
            id: loader
            anchors.bottom: parent.bottom
            sourceComponent: noLogin
            //sourceComponent: MainWindow.username === "" ? noLogin : login
        }

        Component {
            id: login
            FluText {
                id: identity
                text: "普通用户"
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
                    MainWindow.window.loginPageRegister.launch({
                                                                   "username": "admin"
                                                               })
                }
            }
        }
    }
}
