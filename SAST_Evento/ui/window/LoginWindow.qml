import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import FluentUI
import "qrc:///SAST_Evento/ui/component"

CustomWindow {
    id: window
    width: 278
    height: 378
    fixSize: true
    launchMode: FluWindowType.SingleTask
    closeDestory: false
    title: "SAST Evento"

    LoginController {
        onLoginStatusChanged: {
            switch (loginStatus) {
            case 1:
                hideLoading()
                break
            case 2:
                showLoading()
                break
            case 3:
                FluApp.navigate("/")
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
        width: 80
        height: 80
        source: {
            if (settings.value("darkMode",
                               FluThemeType.System) === FluThemeType.Dark) {
                return "qrc:/SAST_Evento/res/image/evento_white.png"
            } else {
                return "qrc:/SAST_Evento/res/image/evento_black.png"
            }
        }

        anchors {
            top: parent.top
            topMargin: 80
            horizontalCenter: parent.horizontalCenter
        }
    }

    FluAutoSuggestBox {
        id: textbox_uesrname
        items: [{
                "title": settings.value("username", "")
            }]
        placeholderText: lang.lang_username
        Layout.preferredWidth: 260
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 40
    }

    FluTextBox {
        id: textbox_password
        Layout.topMargin: 20
        Layout.preferredWidth: 260
        placeholderText: lang.lang_password
        echoMode: TextInput.Password
        Layout.alignment: Qt.AlignHCenter
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
            bottomMargin: 80
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
        }
    }

    FluText {
        text: "V1.0.0"
        color: FluColors.Grey100
        font: FluTextStyle.Caption
        anchors {
            bottom: parent.bottom
            bottomMargin: 26
            horizontalCenter: parent.horizontalCenter
        }
    }

    Settings {
        id: settings
        property int darkMode
        property string username
    }
}
