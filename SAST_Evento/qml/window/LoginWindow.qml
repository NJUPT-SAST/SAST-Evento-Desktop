import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/component"

CustomWindow {

    id: window
    title: lang.lang_login
    width: 400
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
            sourceSize.width: 400
            Layout.alignment: Qt.AlignHCenter
            source: {
                if (settings.value("darkMode",
                                   FluThemeType.System) === FluThemeType.Dark) {
                    return "qrc:/SAST_Evento/res/image/evento_white.png"
                } else {
                    return "qrc:/SAST_Evento/res/image/evento_black.png"
                }
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
            id: btn
            text: lang.lang_login
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
