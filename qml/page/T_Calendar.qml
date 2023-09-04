import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: control
    launchMode: FluPageType.SingleTask

    property string dateString: date2String(new Date)

    function loadAllInfo(date) {
        statusMode = FluStatusViewType.Loading
        CalendarController.loadAllEventoInfo(date)
    }

    Component.onCompleted: {
        loadAllInfo(dateString)
    }

    Connections {
        target: CalendarController
        function onLoadAllEventoSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: CalendarController
        function onLoadAllEventoErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    onErrorClicked: {
        loadAllInfo(dateString)
    }

    Item {
        width: 885
        height: 50

        FluIconButton {
            id: btn_left
            iconSource: FluentIcons.ChevronLeft
            anchors {
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
            onClicked: {
                var date = new Date(date_picker.current)
                date.setDate(date_picker.current.getDate() - 7)
                date_picker.current = date
                dateString = date2String(date)
            }
        }
        FluCalendarPicker {
            id: date_picker
            anchors {
                left: btn_left.right
                verticalCenter: parent.verticalCenter
            }
            current: new Date
            onAccepted: {
                dateString = date_picker.text
                loadAllInfo(dateString)
            }
        }
        FluIconButton {
            id: btn_right
            iconSource: FluentIcons.ChevronRight
            anchors {
                left: date_picker.right
                verticalCenter: parent.verticalCenter
            }
            onClicked: {
                var date = new Date(date_picker.current)
                date.setDate(date_picker.current.getDate() + 7)
                date_picker.current = date
                dateString = date2String(date)
            }
        }

        FluText {
            text: date_picker.current.getFullYear(
                      ) + "年" + (date_picker.current.getMonth() + 1) + "月"
            font.pixelSize: 20
            anchors {
                left: btn_right.right
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }

        FluButton {
            id: btn_type
            text: "类型管理"
            anchors {
                top: parent.top
                topMargin: 10
                right: btn_location.left
                rightMargin: 5
            }

            onClicked: {
                EventoHelper.id = 0
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
            }
        }

        FluButton {
            id: btn_location
            text: "地点管理"
            anchors {
                top: parent.top
                topMargin: 10
                right: btn_department.left
                rightMargin: 5
            }
            onClicked: {
                EventoHelper.id = 0
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
            }
        }

        FluButton {
            id: btn_department
            text: "部门管理"
            anchors {
                top: parent.top
                topMargin: 10
                right: btn_create.left
                rightMargin: 10
            }
            onClicked: {
                EventoHelper.id = 0
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
            }
        }

        FluFilledButton {
            id: btn_create
            text: "创建活动"
            anchors {
                top: parent.top
                topMargin: 10
                right: parent.right
            }

            onClicked: {
                EventoHelper.id = 0
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
            }
        }
    }

    FluArea {
        height: 780
        width: 890
        color: "transparent"
        Row {
            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 100
            }
            spacing: 92

            FluText {
                id: mon
                text: "周一\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 0)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: tue
                text: "周二\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 1)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: wedn
                text: "周三\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 2)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: thur
                text: "周四\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 3)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: fri
                text: "周五\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 4)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: sat
                text: "周六\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 5)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
            FluText {
                id: sun
                text: "周日\n" + getNextDate(getMondayOfWeek(
                                               date_picker.current), 6)
                font: FluTextStyle.BodyStrong
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Column {
            anchors {
                top: parent.top
                topMargin: 50
                left: parent.left
                leftMargin: 10
            }
            spacing: 30

            FluText {
                id: text_8
                text: "08:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_9
                text: "09:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_10
                text: "10:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_11
                text: "11:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_12
                text: "12:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_13
                text: "13:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_14
                text: "14:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_15
                text: "15:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_16
                text: "16:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_17
                text: "17:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_18
                text: "18:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_19
                text: "19:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_20
                text: "20:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_21
                text: "21:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_22
                text: "22:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluText {
                id: text_23
                text: "23:00"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
        }

        Row {
            anchors {
                top: parent.top
                topMargin: 5
                left: parent.left
                leftMargin: 50
            }
            spacing: 119
            Repeater {
                id: rep_date
                model: 7
                FluRectangle {
                    width: 1
                    height: 1130
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    shadow: false
                    color: "#e1dfdd"
                }
            }
        }

        Column {
            anchors {
                top: parent.top
                topMargin: 57
                left: parent.left
                leftMargin: 60
                right: parent.right
            }
            spacing: 44.1
            Repeater {
                id: rep_time
                model: 16
                FluRectangle {
                    width: parent.width
                    height: 1
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    shadow: false
                    color: "#e1dfdd"
                }
            }
        }

        Component.onCompleted: {
            for (var i = 0; i < rep_block.count; i++) {
                var itemModel = rep_block.itemAt(i).model
                rep_block.itemAt(i).x = rep_date.itemAt(
                            itemModel.colunmStart).x + 53
                rep_block.itemAt(i).y = rep_time.itemAt(
                            itemModel.rowStart).y + 60
            }
        }

        Repeater {
            id: rep_block
            model: EventoBlockModel
            delegate: com_rec
        }
    }

    Component {
        id: com_rec
        FluArea {
            height: 43.1 * (model.rowEnd - model.rowStart)
            width: 115
            border.color: FluTheme.primaryColor.normal
            Rectangle {
                anchors.fill: parent
                color: {
                    if (FluTheme.dark) {
                        if (item_mouse.containsMouse) {
                            return Qt.rgba(1, 1, 1, 0.03)
                        }
                        return Qt.rgba(0, 0, 0, 0)
                    } else {
                        if (item_mouse.containsMouse) {
                            return Qt.rgba(0, 0, 0, 0.03)
                        }
                        return Qt.rgba(0, 0, 0, 0)
                    }
                }
            }
            MouseArea {
                id: item_mouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                    // TODO
                }
            }
        }
    }

    function getMondayOfWeek(date) {
        var dayOfWeek = date.getDay()
        var daysToMonday = (dayOfWeek + 6) % 7
        var mondayDate = new Date(date.getTime(
                                      ) - daysToMonday * 24 * 60 * 60 * 1000)
        return mondayDate
    }

    function getNextDate(date, days) {
        var nextDate = new Date(date)
        nextDate.setDate(date.getDate() + days)
        return nextDate.getDate()
    }

    function date2String(date) {
        return date.getFullYear() + "-" + (date.getMonth(
                                               ) + 1) + "-" + date.getDate()
    }
}
