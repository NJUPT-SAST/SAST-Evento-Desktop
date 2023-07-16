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
        property bool rememberPsw
        property string password
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
                                   FluDarkMode.System) === FluDarkMode.Dark) {
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

            Component.onCompleted: {
                if (checkBox.checked) {
                    textbox_password.text = settings.value("password", "")
                }
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
                if (checkBox.checked) {
                    settings.password = textbox_password.text
                } else {
                    settings.password = ""
                }

                onResult({
                             "ok": true,
                             "username": textbox_uesrname.text,
                             "password": textbox_password.text
                         })
                window.hide()
            }
        }

        FluCheckBox {
            id: checkBox
            Layout.topMargin: 10
            Layout.alignment: Qt.AlignCenter
            text: "记住密码"

            Component.onCompleted: {
                if (settings.value("rememberPsw", false).charAt(0) === 't') {
                    checked = true
                } else {
                    checked = false
                }
            }

            clickListener: function () {
                checked = !checked
                settings.rememberPsw = checkBox.checked
            }
        }
    }
}
