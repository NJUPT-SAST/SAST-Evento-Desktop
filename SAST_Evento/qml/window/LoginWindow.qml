import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/component"

CustomWindow {

    id: window
    title: "登录"
    width: 400
    height: 400
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

        FluAutoSuggestBox {
            id: textbox_uesrname
            items: [{
                    "title": settings.value("username", "")
                }]
            placeholderText: "账号"
            Layout.preferredWidth: 260
            Layout.alignment: Qt.AlignHCenter
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
                if (checked !== settings.rememberPsw) {
                    checked = settings.rememberPsw
                }
            }

            clickListener: function () {
                checked = !checked
                settings.rememberPsw = checkBox.checked
            }
        }
    }
}
