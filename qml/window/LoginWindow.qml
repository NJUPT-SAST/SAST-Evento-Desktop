import FluentUI
import Qt.labs.platform
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SAST_Evento

FluWindow {
    id: window

    property bool loginSuccess: false

    title: lang.lang_login
    width: 278
    height: 378
    fixSize: true
    launchMode: FluWindowType.SingleTask
    Component.onCompleted: {
    }

    Connections {
        function onLoginProcessing() {
            showLoading();
        }

        target: LoginController
    }

    Connections {
        function onLoginSuccess() {
            loginSuccess = true;
            LoginController.loadPermissionList();
        }

        target: LoginController
    }

    Connections {
        function onLoadPermissionSuccessEvent() {
            hideLoading();
            FluRouter.navigate("/");
            window.close();
        }

        target: LoginController
    }

    Connections {
        function onLoadPermissionErrorEvent(message) {
            hideLoading();
            showError(lang.lang_error + message, 4000);
        }

        target: LoginController
    }

    Connections {
        function onLoginFailed(reason) {
            hideLoading();
            system_tray.showMessage(lang.lang_login_failed, lang.lang_error + reason);
            window.requestActivate();
            showError(lang.lang_login_failed, 4000);
        }

        target: LoginController
    }

    Image {
        id: logo

        height: 80
        fillMode: Image.PreserveAspectFit
        source: {
            if (FluTheme.dark)
                return "qrc:/res/image/evento_white.png";
            else
                return "qrc:/res/image/evento_black.png";
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
        onActivated: (reason) => {
            if (reason === SystemTrayIcon.Trigger) {
                window.show();
                window.raise();
                window.requestActivate();
            }
        }

        menu: Menu {
            MenuItem {
                text: lang.lang_exit
                onTriggered: {
                    window.deleteWindow();
                    FluApp.closeApp();
                }
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
        focus: true
        onClicked: {
            if (loginSuccess)
                LoginController.loadPermissionList();
            else
                LoginController.beginLoginViaSastLink();
        }

        anchors {
            bottom: parent.bottom
            bottomMargin: 110
            horizontalCenter: parent.horizontalCenter
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

        text: lang.lang_guest_login
        iconSource: FluentIcons.GuestUser
        display: Button.TextBesideIcon
        onClicked: {
            UserHelper.permission = UserHelper.GuestPermission;
            FluRouter.navigate("/");
            window.close();
        }

        anchors {
            top: btn_login.bottom
            topMargin: 8
            horizontalCenter: parent.horizontalCenter
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
