import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/component"

CustomWindow {

    id: window
    title: "登录"
    width: 500
    height: 500
    fixSize: true
    modality: Qt.ApplicationModal
    closeFunc: function (event) {
        onResult({
                     "ok": false
                 })
    }

    Settings {
        id: settings
        property int darkMode
    }

    onInitArgument: argument => {
                        if (argument.username === "") {
                            textbox_uesrname.focus = true
                        } else {
                            textbox_uesrname.updateText(argument.username)
                            textbox_password.focus = true
                        }
                    }

    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        Image {
            source: "qrc:/SAST_Evento/res/image/evento_black.png"
            sourceSize.width: 450
            Layout.alignment: Qt.AlignHCenter
            Component.onCompleted: {
                if (settings.value("darkMode",
                                   FluThemeType.System) === FluThemeType.Dark) {
                    source = "qrc:/SAST_Evento/res/image/evento_white.png"
                }
            }
        }

        FluAutoSuggestBox {
            id: textbox_uesrname
            items: [{
                    "title": settings.value("username", "")
                }]
            placeholderText: "账号"
            Layout.preferredWidth: 260
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 40
        }

        FluTextBox {
            id: textbox_password
            Layout.topMargin: 20
            Layout.preferredWidth: 260
            placeholderText: "密码"
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
            id: btn
            text: "登录"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
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

                onResult({
                             "ok": true,
                             "username": textbox_uesrname.text,
                             "password": textbox_password.text
                         })
                window.hide()
            }
        }
    }
}
