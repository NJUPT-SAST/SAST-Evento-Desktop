import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    FluFilledButton {
        text: "创建活动"
        Layout.topMargin: 10
        Layout.alignment: Qt.AlignRight
        Layout.rightMargin: 10
        onClicked: {
            EventoHelper.id = 0
            MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
        }
    }
}
