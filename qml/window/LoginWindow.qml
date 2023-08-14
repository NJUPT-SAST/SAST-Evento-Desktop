import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import FluentUI
import SAST_Evento
import "../imports"

CustomWindow {
    id: window
    width: 278
    height: 378
    fixSize: true
    launchMode: FluWindowType.SingleTask
    closeDestory: true
    title: "SAST Evento"

    Connections {
        target: LoginController
        function onLoginStatusChanged() {
            switch (loginStatus) {
            case 1:
                hideLoading()
                break
            case 2:
                showLoading()
                break
            case 3:
                FluApp.navigate("/")
                settings.username = textbox_uesrname.text
                window.close()
                break
            case 4:
                hideLoading()
                showError("账号或密码错误")
                break
            default:
                break
            }
        }
    }

    Image {
        id: logo
        height: 80
        fillMode: Image.PreserveAspectFit
        source: {
            if (settings.value("darkMode",
                               FluThemeType.System) === FluThemeType.Dark) {
                return "qrc:/res/image/evento_white.png"
            } else {
                return "qrc:/res/image/evento_black.png"
            }
        }

        anchors {
            top: parent.top
            topMargin: 25
            horizontalCenter: parent.horizontalCenter
        }
    }

    FluAutoSuggestBox {
        id: textbox_uesrname
        anchors {
            top: logo.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
        items: [{
                "title": settings.value("username", "")
            }]
        placeholderText: lang.lang_username
        width: 180
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 40
    }

    FluTextBox {
        id: textbox_password
        anchors {
            top: textbox_uesrname.bottom
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }

        width: 180
        placeholderText: lang.lang_password
        echoMode: TextInput.Password
        Keys.onEnterPressed: {
            btn.clicked()
        }
        Keys.onReturnPressed: {
            btn.clicked()
        }
    }

    FluFilledButton {
        text: lang.lang_login
        width: 180
        height: 36
        anchors {
            bottom: parent.bottom
            bottomMargin: 60
            horizontalCenter: parent.horizontalCenter
        }
        focus: true
        onClicked: {
            if (textbox_uesrname.text === "") {
                showError("账号为空")
                return
            }
            if (textbox_password.text === "") {
                showError("密码为空")
                return
            }

            // TODO
            FluApp.navigate("/")
            settings.username = textbox_uesrname.text
            window.close()
        }
    }

    FluText {
        text: "V0.2.8.9"
        color: FluColors.Grey100
        font: FluTextStyle.Caption
        anchors {
            bottom: parent.bottom
            bottomMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
    }

    Settings {
        id: settings
        property int darkMode
        property string username
    }
}
