import QtQuick
import QtQuick.Window
import FluentUI

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    FluButton {
        text: "test"
    }
}
