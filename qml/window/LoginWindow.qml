import QtQuick
import Qt.labs.platform
import QtQuick.Layouts
import QtQuick.Controls
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
    title: lang.lang_login
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
            window.requestActivate()
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
        height: 80
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

    FluButton {
        id: btn_login
        text: lang.lang_use_link
        font.pixelSize: 16
        font.bold: true
        textColor: Qt.rgba(250 / 255, 250 / 255, 250 / 255, 1)
        width: 190
        height: 45
        normalColor: Qt.rgba(28 / 255, 31 / 255, 36 / 255, 1)
        hoverColor: Qt.rgba(38 / 255, 41 / 255, 46 / 255, 1)
        anchors {
            bottom: parent.bottom
            bottomMargin: 110
            horizontalCenter: parent.horizontalCenter
        }
        focus: true
        onClicked: {
            if (loginSuccess)
                LoginController.loadPermissionList()
            else
                FluApp.navigate("/")
            //LoginController.beginLoginViaSastLink()
        }
    }

    Image {
        width: implicitWidth
        height: implicitHeight
        source: "qrc:/res/svg/sast_link.svg"
        anchors {
            verticalCenter: btn_login.verticalCenter
            left: btn_login.left
            leftMargin: 20
        }
    }

    FluIconButton {
        id: btn_visitor
        text: lang.lang_visitor_login
        iconSource: FluentIcons.GuestUser
        display: Button.TextBesideIcon
        anchors {
            top: btn_login.bottom
            topMargin: 8
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: {
            UserHelper.permission = 1
            FluApp.navigate("/")
            window.close()
        }
    }

    FluText {
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
}
