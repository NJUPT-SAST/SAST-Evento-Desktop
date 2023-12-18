import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: calendar
    launchMode: FluPageType.SingleTask

    property string dateString: date2String(new Date)
    property var blockWindowRegister: registerForWindowResult("/block")

    function load() {
        statusMode = FluStatusViewType.Loading
        CalendarController.loadAllEventoInfo(dateString)
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

    Connections {
        target: CalendarController
        function onDeleteSuccessEvent() {
            showSuccess("删除成功")
            load()
        }
    }

    Connections {
        target: CalendarController
        function onDeleteErrorEvent(message) {
            showError("错误：" + message)
        }
    }

    Connections {
        target: CalendarController
        function onLoadPicSuccessEvent() {
            pushPage("qrc:/qml/page/T_LessonPic.qml")
        }
    }

    Connections {
        target: CalendarController
        function onLoadPicErrorEvent(message) {
            showError("课表生成错误：" + message)
        }
    }

    Connections {
        target: blockWindowRegister
        function onResult(data) {
            if (data.enterPage) {
                pushPage("qrc:/qml/page/T_EventoEdit.qml")
                showInfo("注意：活动地点需要重新编辑", 4000)
            }
        }
    }

    function pushPage(url) {
        MainWindow.window.pushPage(url)
    }

    Component.onCompleted: {
        load()
    }

    onErrorClicked: {
        load()
    }

    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Item {
        Layout.fillWidth: true
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
                let date = new Date(date_picker.current)
                date.setDate(date_picker.current.getDate() - 7)
                date_picker.current = date
                dateString = date2String(date_picker.current)
                load()
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
                load()
            }
        }

        FluArea {
            id: rec_date
            height: 30
            width: 120
            radius: [4, 4, 4, 4]
            anchors {
                left: btn_left.right
                verticalCenter: parent.verticalCenter
            }
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
                let date = new Date(date_picker.current)
                date.setDate(date_picker.current.getDate() + 7)
                date_picker.current = date
                dateString = date2String(date_picker.current)
                load()
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
        FluButton {
            id: btn_SRD_lesson_pic
            text: "本周软研课表"
            anchors {
                top: parent.top
                topMargin: 10
                right: btn_create.left
                rightMargin: 10
            }
            onClicked: {
                CalendarController.generateLessonPic(dateString, CalendarController.SoftwareResearchAndDevelopmentDep)
            }
        }

        FluFilledButton {
            id: btn_create
            text: "创建活动"
            anchors {
                top: parent.top
                topMargin: 10
                right: parent.right
                rightMargin: 10
            }

            onClicked: {
                EventoEditController.isEditMode = false
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml")
            }
        }
    }

    FluArea {
        id: table
        height: 765 + all_day_height
        width: parent.width > 890 ? parent.width : 890
        color: "transparent"

        readonly property int blockHeight: 45
        readonly property int blockWidth: (width - 50) / 7
        readonly property int all_day_height : EventoBlockModel.all_day_line_num * blockHeight

        Row {
            id: weekTitle
            anchors {
                top: parent.top
                topMargin: 20
                left: parent.left
                leftMargin: 50
            }

            Repeater {
                model: ListModel {
                    ListElement {
                        title: "周一\n"
                    }
                    ListElement {
                        title: "周二\n"
                    }
                    ListElement {
                        title: "周三\n"
                    }
                    ListElement {
                        title: "周四\n"
                    }
                    ListElement {
                        title: "周五\n"
                    }
                    ListElement {
                        title: "周六\n"
                    }
                    ListElement {
                        title: "周日\n"
                    }
                }

                delegate: FluText {
                    width: table.blockWidth
                    text: title + getDate(getMondayOfWeek(date_picker.current), index)
                    font: FluTextStyle.BodyStrong
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        FluText {
            anchors {
                top: weekTitle.bottom
                topMargin: 10
            }

            height: table.all_day_height
            width: 50
            text: "Multi\nDay"
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignHCenter
            visible: EventoBlockModel.all_day_line_num
        }

        Repeater {
            model: EventoBlockModel.all_day_line_num

            delegate: FluRectangle {
                anchors {
                    top: weekTitle.bottom
                    topMargin: 10 + index * table.blockHeight
                    left: parent.left
                    leftMargin: 50
                    right: parent.right
                    rightMargin: 10
                }
                Layout.fillWidth: true
                height: 1
                color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255,
                                               62 / 255, 1) : "#e1dfdd"
            }
        }

        Row {
            anchors {
                top: parent.top
                topMargin: 5
                left: parent.left
                leftMargin: 50
            }
            spacing: table.blockWidth - 1

            Repeater {
                model: 7
                delegate: FluRectangle {
                    width: 1
                    height: table.height - 28
                    color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255,
                                                   62 / 255, 1) : "#e1dfdd"
                }
            }
        }

        Repeater {
            model: ListModel {
                ListElement {
                    title: "8:00"
                }
                ListElement {
                    title: "9:00"
                }
                ListElement {
                    title: "10:00"
                }
                ListElement {
                    title: "11:00"
                }
                ListElement {
                    title: "12:00"
                }
                ListElement {
                    title: "13:00"
                }
                ListElement {
                    title: "14:00"
                }
                ListElement {
                    title: "15:00"
                }
                ListElement {
                    title: "16:00"
                }
                ListElement {
                    title: "17:00"
                }
                ListElement {
                    title: "18:00"
                }
                ListElement {
                    title: "19:00"
                }
                ListElement {
                    title: "20:00"
                }
                ListElement {
                    title: "21:00"
                }
                ListElement {
                    title: "22:00"
                }
                ListElement {
                    title: "23:00"
                }

            }

            delegate: Item {
                anchors {
                    top: weekTitle.bottom
                    topMargin: 10 + index * table.blockHeight + table.all_day_height
                    left: parent.left
                    right: parent.right
                }

                FluRectangle {
                    id: row_line
                    anchors {
                        top: parent.top
                        left: parent.left
                        leftMargin: 50
                        right: parent.right
                        rightMargin: 10
                    }
                    Layout.fillWidth: true
                    height: 1
                    color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255,
                                                   62 / 255, 1) : "#e1dfdd"
                }

                FluText {
                    anchors {
                        left: parent.left
                        right: row_line.left
                        verticalCenter: row_line.top
                    }
                    text: title
                    font: FluTextStyle.Caption
                    color: FluColors.Grey110
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        Repeater {
            model: EventoBlockModel

            delegate: FluArea {
                readonly property double width_min : table.blockWidth / (depth_max + 1)

                anchors {
                    top: weekTitle.bottom
                    topMargin: is_all_day ? 10 + depth * table.blockHeight : 10 + table.all_day_height + start * table.blockHeight
                    left: parent.left
                    leftMargin: is_all_day ? 50 + start * table.blockWidth : 50 + column * table.blockWidth + depth * width_min
                }

                height: is_all_day ? table.blockHeight : table.blockHeight * (end - start)
                width: is_all_day ? table.blockWidth * (end - start) : (depth == depth_max ? 1 : 1.618) * width_min
                color: FluTheme.dark ? Qt.rgba(23 / 255, 49 / 255, 102 / 255, 1) : Qt.rgba(224 / 255, 233 / 255, 255 / 255, 1)

                FluRectangle {
                    width: 4
                    height: parent.height - 8
                    color: FluColors.Blue.normal
                    radius: [2, 2, 2, 2]
                    anchors {
                        left: parent.left
                        leftMargin: 3
                        verticalCenter: parent.verticalCenter
                    }
                }
                FluText {
                    id: text_title
                    text: title
                    font: FluTextStyle.BodyStrong
                    elide: Text.ElideRight
                    maximumLineCount: parent.height > 55 ? 2 : 1
                    wrapMode: Text.WordWrap
                    anchors {
                        top: parent.top
                        topMargin: 5
                        left: parent.left
                        right: parent.right
                        leftMargin: 13
                        rightMargin: 3
                    }
                }

                FluText {
                    text: time
                    font: FluTextStyle.Caption
                    color: FluColors.Grey110
                    elide: Text.ElideRight
                    maximumLineCount: 1
                    anchors {
                        top: text_title.bottom
                        topMargin: 2
                        left: text_title.left
                        right: parent.right
                    }
                }

                MouseArea {
                    id: event_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: mouse => {
                        if (mouse.button === Qt.LeftButton) {
                            EventoHelper.id = id
                            EventoInfoController.editable = editable
                            blockWindowRegister.launch()
                        }
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    color: {
                        if (!editable) {
                            return FluTheme.dark ? Qt.rgba(
                                                           33 / 255, 45 / 255,
                                                           69 / 255,
                                                           0.5) : Qt.rgba(241 / 255, 245
                                                                          / 255, 255 / 255, 0.5)
                        }
                        if (FluTheme.dark) {
                            if (event_mouse.containsMouse) {
                                    return Qt.rgba(1, 1, 1, 0.03)
                            }
                            return Qt.rgba(0, 0, 0, 0)
                        } else {
                            if (event_mouse.containsMouse) {
                                return Qt.rgba(0, 0, 0, 0.03)
                            }
                            return Qt.rgba(0, 0, 0, 0)
                        }
                    }
                }
            }
        }
    }

    function getMondayOfWeek(date) {
        let dayOfWeek = (date.getDay() + 6) % 7
        let result = new Date(date)
        result.setDate(date.getDate() - dayOfWeek)
        return result
    }

    function getDate(monday, dayOfWeek) {
        let result = new Date(monday)
        result.setDate(monday.getDate() + dayOfWeek)
        return (result.getMonth() + 1) + "/" + result.getDate()
    }

    function date2String(date) {
        return date.getFullYear() + "-" + (date.getMonth() + 1) + "-" + date.getDate()
    }
}
