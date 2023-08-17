import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    title: lang.lang_schedule
    launchMode: FluPageType.SingleTask

    ListView {
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false

        Component.onCompleted: {
            model = getEventItems()
        }
    }

    function getEventItems() {
        var arr = []
        for (var i = 0; i < 10; ++i) {
            arr.push({
                         "image": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                         "title": "活动卡片",
                         "time": "2023.07.10 15:00-17:00",
                         "id": i
                     })
        }
        return arr
    }
}
