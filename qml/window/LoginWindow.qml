import QtQuick
import Qt.labs.platform
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI
import SAST_Evento
import org.wangwenx190.FramelessHelper

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
        if (FluTheme.dark) {
            FramelessUtils.systemTheme = FramelessHelperConstants.Dark
        }
        else
            FramelessUtils.systemTheme = FramelessHelperConstants.Light
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
            verticalCenter: btn_login.verticalCenter
            left: btn_login.left
            leftMargin: 20
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
            bottomMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
    }
}
