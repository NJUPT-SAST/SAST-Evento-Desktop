import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    property string dateString: date2String(new Date)
    property var rowStartArr: []
    property var columnStartArr: []

    property var blockWindowRegister: registerForWindowResult("/block")

    function loadAllInfo(date) {
        statusMode = FluStatusViewType.Loading
        CalendarController.loadAllEventoInfo(date)
    }

    Loader {
        id: loader
        sourceComponent: undefined
    }

    Component {
        id: com_model
        Repeater {
            id: rep_model
            model: EventoBlockModel
            Item {
                Component.onCompleted: {
                    rowStartArr.push(model.rowStart)
                    columnStartArr.push(model.columnStart)
                }
            }
        }
    }

    Connections {
        target: CalendarController
        function onLoadAllEventoSuccessEvent() {
            rowStartArr = []
            columnStartArr = []
            loader.sourceComponent = com_model
            for (var i = 0; i < rep_block.count; i++) {
                rep_block.itemAt(i).x = rep_date.itemAt(
                            columnStartArr[i]).x + 53
                rep_block.itemAt(i).y = rep_time.itemAt(
                            parseInt(
                                rowStartArr[i])).y + 60 + (rowStartArr[i] - parseInt(
                                                               rowStartArr[i])) * 43.1
            }
            loader.sourceComponent = undefined
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

    Connections {
        target: CalendarController
        function onDeleteSuccessEvent() {
            showSuccess("删除成功")
            loadAllInfo(dateString)
        }
    }

    Connections {
        target: CalendarController
        function onDeleteErrorEvent(message) {
            showError("错误：" + message)
        }
    }

    Connections {
        target: blockWindowRegister
        function onResult(data) {
            if (data.enterPage) {
                pushPage()
            }
        }
    }

    function pushPage() {
        MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
    }

    Component.onCompleted: {
        loadAllInfo(dateString)
    }

    onErrorClicked: {
        loadAllInfo(dateString)
    }

    errorButtonText: lang.lang_reload

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
                loadAllInfo(dateString)
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
                dateString = date2String(date_picker.current)
                loadAllInfo(dateString)
            }
        }
        FluRectangle {
            id: rec_date
            height: 30
            width: 120
            radius: [4, 4, 4, 4]
            anchors {
                left: btn_left.right
                verticalCenter: parent.verticalCenter
            }
            shadow: false
            FluText {
                id: text_date
                text: dateString
                anchors.centerIn: parent
            }
            Rectangle {
                anchors.fill: parent
                radius: 8
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
                propagateComposedEvents: true
                onClicked: function (mouse) {
                    mouse.accepted = false
                }
                onPressed: function (mouse) {
                    mouse.accepted = false
                }
                onReleased: function (mouse) {
                    mouse.accepted = false
                }
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
                loadAllInfo(dateString)
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

        // deprecated


        /*
        Item {
            visible: false
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
                    MainWindow.window.pushPage(
                                "qrc:/qml/page/T_TypeManagement.qml")
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
                    MainWindow.window.pushPage(
                                "qrc:/qml/page/T_LocationManagement.qml")
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
                    MainWindow.window.pushPage(
                                "qrc:/qml/page/T_DepartmentManagement.qml")
                }
            }
        }
        */
        FluFilledButton {
            id: btn_create
            text: "创建活动"
            anchors {
                top: parent.top
                topMargin: 10
                right: parent.right
            }

            onClicked: {
                EventoEditController.isEditMode = false
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

            Repeater {
                model: [{
                        "text": "周一\n",
                        "index": 0
                    }, {
                        "text": "周二\n",
                        "index": 1
                    }, {
                        "text": "周三\n",
                        "index": 2
                    }, {
                        "text": "周四\n",
                        "index": 3
                    }, {
                        "text": "周五\n",
                        "index": 4
                    }, {
                        "text": "周六\n",
                        "index": 5
                    }, {
                        "text": "周日\n",
                        "index": 6
                    }]
                FluText {
                    text: modelData.text + getNextDate(
                              getMondayOfWeek(date_picker.current),
                              modelData.index)
                    font: FluTextStyle.BodyStrong
                    horizontalAlignment: Text.AlignHCenter
                }
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

            Repeater {
                model: ["8:00", "9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00", "21:00", "22:00", "23:00"]
                FluText {
                    text: model.modelData
                    font: FluTextStyle.Caption
                    color: FluColors.Grey110
                }
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
                    color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255,
                                                   62 / 255, 1) : "#e1dfdd"
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
                    color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255,
                                                   62 / 255, 1) : "#e1dfdd"
                }
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
            height: 41.1 * (model.rowEnd - model.rowStart) + parseInt(
                        model.rowEnd - model.rowStart - 1)
            width: 115
            color: FluTheme.dark ? Qt.rgba(
                                       23 / 255, 49 / 255, 102 / 255,
                                       1) : Qt.rgba(224 / 255, 233 / 255, 255 / 255, 1)

            FluRectangle {
                width: 4
                height: parent.height - 8
                color: FluColors.Blue.normal
                radius: [2, 2, 2, 2]
                shadow: false
                anchors {
                    left: parent.left
                    leftMargin: 3
                    verticalCenter: parent.verticalCenter
                }
            }

            FluText {
                id: text_title
                text: model.title
                font: FluTextStyle.BodyStrong
                elide: Text.ElideRight
                maximumLineCount: parent.height > 55 ? 2 : 1
                wrapMode: Text.WordWrap
                anchors {
                    top: parent.top
                    topMargin: parent.height / 2 - 15
                    left: parent.left
                    right: parent.right
                    leftMargin: 13
                    rightMargin: 3
                }
            }
            FluText {
                text: model.time
                font: FluTextStyle.Caption
                color: FluColors.Grey110
                anchors {
                    top: text_title.bottom
                    topMargin: 2
                    left: text_title.left
                }
            }

            MouseArea {
                id: item_mouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    EventoHelper.id = model.id
                    EventoInfoController.editable = model.editable
                    blockWindowRegister.launch()
                }
            }

            Rectangle {
                anchors.fill: parent
                color: {
                    if (!model.editable) {
                        return FluTheme.dark ? Qt.rgba(
                                                   33 / 255, 45 / 255,
                                                   69 / 255,
                                                   0.5) : Qt.rgba(241 / 255, 245
                                                                  / 255, 255 / 255, 0.5)
                    }
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
