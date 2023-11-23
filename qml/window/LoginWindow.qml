import QtQuick
import Qt.labs.platform
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI
import SAST_Evento

FluWindow {
    id: window
    title: lang.lang_login
    width: 320
    height: 448
    fixSize: true
    launchMode: FluWindowType.SingleTask
    closeDestory: true

    property bool loginSuccess: false

    Component.onCompleted: {
        loginSuccess = false
    }

    Connections {
        target: LoginController

        function onLoginProcessing() {
            showLoading()
        }
    }

    Connections {
        target: LoginController

        function onLoginSuccess() {
            loginSuccess = true
            LoginController.loadPermissionList()
        }
    }

    Connections {
        target: LoginController

        function onLoadPermissionSuccessEvent() {
            hideLoading()
            FluApp.navigate("/")
            window.close()
        }
    }

    Connections {
        target: LoginController

        function onLoadPermissionErrorEvent(message) {
            hideLoading()
            showError(lang.lang_error + message, 4000)
        }
    }

    Connections {
        target: LoginController

        function onLoginFailed(reason) {
            hideLoading()
            system_tray.showMessage(lang.lang_login_failed,
                                    lang.lang_error + reason)
            window.requestActivate()
            showError(lang.lang_login_failed, 4000)
        }
    }

    Image {
        id: logo
        height: 60
        fillMode: Image.PreserveAspectFit
        source: {
            if (FluTheme.dark) {
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

    Loader {
        id: loader
        width: 320
        height: 230
        anchors {
            top: logo.bottom
            horizontalCenter: parent.horizontalCenter
        }

        Component.onCompleted: {
            sourceComponent = com_link_login
            link_login.disabled = true
        }
    }

    Component {
        id: com_link_login
        Item {
            anchors.fill: parent
            anchors.centerIn: parent
            FluButton {
                id: btn_login1
                text: lang.lang_use_link
                font.pixelSize: 16
                font.bold: true
                textColor: Qt.rgba(250 / 255, 250 / 255, 250 / 255, 1)
                width: 190
                height: 45
                normalColor: Qt.rgba(28 / 255, 31 / 255, 36 / 255, 1)
                hoverColor: Qt.rgba(38 / 255, 41 / 255, 46 / 255, 1)
                anchors.centerIn: parent
                focus: true
                onClicked: {
                    if (loginSuccess)
                        LoginController.loadPermissionList()
                    else
                        LoginController.beginLoginViaSastLink()
                }
            }

            Image {
                width: implicitWidth
                height: implicitHeight
                source: "qrc:/res/svg/sast_link.svg"
                anchors {
                    verticalCenter: btn_login1.verticalCenter
                    left: btn_login1.left
                    leftMargin: 20
                }
            }
        }
    }

    Component {
        id: com_username_login
        Item {
            anchors.fill: parent
            anchors.centerIn: parent
            FluTextBox {
                id: txt_username
                placeholderText: lang.lang_username
                width: parent.width - 30
                height: 45
                anchors {
                    top: parent.top
                    topMargin: 20
                    horizontalCenter: parent.horizontalCenter
                }
            }
            FluTextBox {
                id: txt_password
                placeholderText: lang.lang_password
                width: parent.width - 30
                height: 45
                anchors {
                    top: txt_username.bottom
                    topMargin: 15
                    horizontalCenter: parent.horizontalCenter
                }
                echoMode: TextInput.Password
            }

            FluFilledButton {
                id: btn_login
                text: lang.lang_login
                font.pixelSize: 16
                font.bold: true
                enabled: txt_username.text.length > 0
                         && txt_password.text.length > 0
                width: 190
                height: 45
                anchors {
                    top: txt_password.bottom
                    topMargin: 15
                    horizontalCenter: parent.horizontalCenter
                }
                focus: true
                onClicked: {
                    if (loginSuccess)
                        LoginController.loadPermissionList()
                    else
                        LoginController.beginLoginViaUsername(
                                    txt_username.text, txt_password.text)
                }
            }
        }
    }

    Component {
        id: com_qrcode_login
        Item {
            anchors.fill: parent
            anchors.centerIn: parent
            FluText {
                id: text_scan_qrcode
                text: lang.lang_login_hint
                font: FluTextStyle.Caption
                anchors.topMargin: 60
                anchors.horizontalCenter: parent.horizontalCenter
            }
            FluQRCode {
                size: 200
                text: "qrcode"
                anchors.top: text_scan_qrcode.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Row {
        anchors {
            bottom: txt_info.top
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 5
        FluTextButton {
            id: btn_visitor
            text: lang.lang_guest_login
            onClicked: {
                UserHelper.permission = 1
                FluApp.navigate("/")
                window.close()
            }
        }
        FluTextButton {
            id: qrcode_login
            text: lang.lang_scan_login
            onClicked: {
                loader.sourceComponent = com_qrcode_login
                qrcode_login.disabled = true
                username_login.disabled = false
                link_login.disabled = false
            }
        }
        FluTextButton {
            id: username_login
            text: lang.lang_username_login
            onClicked: {
                loader.sourceComponent = com_username_login
                qrcode_login.disabled = false
                username_login.disabled = true
                link_login.disabled = false
            }
        }
        FluTextButton {
            id: link_login
            text: lang.lang_Link_login
            onClicked: {
                loader.sourceComponent = com_link_login
                qrcode_login.disabled = false
                username_login.disabled = false
                link_login.disabled = true
            }
        }
    }

    FluText {
        id: txt_info
        text: lang.lang_by_cpp + appInfo.version
        color: FluColors.Grey100
        font: FluTextStyle.Caption
        horizontalAlignment: Text.AlignHCenter
        lineHeight: 1.5
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/app.ico"
        tooltip: "SAST Evento"
        menu: Menu {
            MenuItem {
                text: lang.lang_exit
                onTriggered: {
                    window.deleteWindow()
                    FluApp.closeApp()
                }
            }
        }
        onActivated: reason => {
                         if (reason === SystemTrayIcon.Trigger) {
                             window.show()
                             window.raise()
                             window.requestActivate()
                         }
                     }
    }
}
