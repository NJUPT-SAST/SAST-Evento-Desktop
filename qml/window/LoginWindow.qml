import QtQuick
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

    Connections {
        target: LoginController
        function onLoginProcessing() {
            showLoading()
        }
    }

    Connections {
        target: LoginController
        function onLoginSuccess() {
            hideLoading()
            FluApp.navigate("/")
            window.close()
        }
    }

    Connections {
        target: LoginController
        function onLoginFailed(reason) {
            hideLoading(reason)
            showError(reason)
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
        text: "       使用 Link 登入"
        font.pixelSize: 16
        font.bold: true
        textColor: Qt.rgba(250 / 255, 250 / 255, 250 / 255, 1)
        width: 190
        height: 45
        normalColor: Qt.rgba(28 / 255, 31 / 255, 36 / 255, 1)
        hoverColor: Qt.rgba(38 / 255, 41 / 255, 46 / 255, 1)
        anchors {
            bottom: parent.bottom
            bottomMargin: 100
            horizontalCenter: parent.horizontalCenter
        }
        focus: true
        onClicked: {
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
        text: "SAST-C++组开发\nV0.2.9.4 alpha"
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
