import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI
import "qrc:///SAST_Evento/qml/component"

CustomWindow {

    id: window
    title: "登录"
    width: 400
    height: 400
    fixSize: true

    closeFunc: function (event) {
        event.accepted = false
        dialog_close.open()
    }

    onInitArgument: argument => {
                        textbox_uesrname.updateText(argument.username)
                        textbox_password.focus = true
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
                    "title": "Admin"
                }, {
                    "title": "User"
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
        }

        FluFilledButton {
            text: "登录"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                if (textbox_password.text === "") {
                    showError("密码为空")
                    return
                }
                onResult({
                             "password": textbox_password.text
                         })
                FluApp.navigate("/")
                window.hide()
            }
        }
    }

    FluContentDialog {
        id: dialog_close
        title: "退出"
        message: "确定要退出程序吗？"

        buttonFlags: FluContentDialog.NeutralButton | FluContentDialog.PositiveButton

        positiveText: "退出"
        neutralText: "取消"

        onPositiveClicked: {
            window.deleteWindow()
            FluApp.closeApp()
        }
    }
}
