import "../component"
import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluContentStatusPage {
    id: calendar

    function getStartOfWeek_Monday(date) {
        const day = date.getDay();
        const diff = date.getDate() - day + (day === 0 ? -6 : 1);
        const startOfWeek = new Date(date);
        startOfWeek.setDate(diff);
        startOfWeek.setHours(0, 0, 0, 0);
        return startOfWeek;
    }

    function load() {
        statusMode = FluStatusLayoutType.Loading;
        CalendarController.loadAllEventoInfo(date2String(date_picker.current));
    }

    function pushPage(url) {
        MainWindow.window.pushPage(url);
    }

    function getMondayOfWeek(date) {
        let dayOfWeek = (date.getDay() + 6) % 7;
        let result = new Date(date);
        result.setDate(date.getDate() - dayOfWeek);
        return result;
    }

    function getDate(monday, dayOfWeek) {
        let result = new Date(monday);
        result.setDate(monday.getDate() + dayOfWeek);
        return (result.getMonth() + 1) + "/" + result.getDate();
    }

    function date2String(date) {
        return date.getFullYear() + "-" + (date.getMonth() + 1) + "-" + date.getDate();
    }

    launchMode: FluPageType.SingleTask
    Component.onCompleted: {
        load();
    }
    onErrorClicked: {
        load();
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    FluWindowResultLauncher {
        id: blockWindowLauncher

        path: "/block"
        onResult: (data) => {
            if (data.enterPage) {
                pushPage("qrc:/qml/page/T_EventoEdit.qml");
                showInfo("注意：活动地点需要重新编辑", 4000);
            }
        }
    }

    Connections {
        function onLoadAllEventoSuccessEvent() {
            statusMode = FluStatusLayoutType.Success;
        }

        target: CalendarController
    }

    Connections {
        function onLoadAllEventoErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: CalendarController
    }

    Connections {
        function onDeleteSuccessEvent() {
            showSuccess("删除成功");
            load();
        }

        target: CalendarController
    }

    Connections {
        function onDeleteErrorEvent(message) {
            showError("错误：" + message);
        }

        target: CalendarController
    }

    Connections {
        function onLoadPicSuccessEvent() {
            pushPage("qrc:/qml/page/T_LessonPic.qml");
        }

        target: CalendarController
    }

    Connections {
        function onLoadPicErrorEvent(message) {
            showError("课表生成错误：" + message);
        }

        target: CalendarController
    }

    Item {
        // deprecated

        height: 50
        width: calendar.width - 35

        FluIconButton {
            id: btn_left

            iconSource: FluentIcons.ChevronLeft
            onClicked: {
                let date = new Date(date_picker.current);
                date.setDate(date_picker.current.getDate() - 7);
                date_picker.current = date;
                load();
            }

            anchors {
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }

        }

        FluCalendarPicker {
            id: date_picker

            current: new Date
            onAccepted: {
                load();
            }

            anchors {
                left: btn_left.right
                verticalCenter: parent.verticalCenter
            }

        }

        FluIconButton {
            id: btn_right

            iconSource: FluentIcons.ChevronRight
            onClicked: {
                let date = new Date(date_picker.current);
                date.setDate(date_picker.current.getDate() + 7);
                date_picker.current = date;
                load();
            }

            anchors {
                left: date_picker.right
                verticalCenter: parent.verticalCenter
            }

        }

        FluText {
            text: date_picker.current.getFullYear() + "年" + (date_picker.current.getMonth() + 1) + "月"
            font.pixelSize: 20

            anchors {
                left: btn_right.right
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }

        }

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
            visible: getStartOfWeek_Monday(date_picker.current).getTime() === getStartOfWeek_Monday(new Date).getTime()
            onClicked: {
                CalendarController.generateLessonPic(date2String(date_picker.current), CalendarController.SoftwareResearchAndDevelopmentDep);
            }

            anchors {
                top: parent.top
                topMargin: 10
                right: UserHelper.permission == UserHelper.AdminPermission ? btn_create.left : parent.right
                rightMargin: 10
            }

        }

        FluFilledButton {
            id: btn_create

            text: "创建活动"
            visible: UserHelper.permission == UserHelper.AdminPermission
            onClicked: {
                EventoEditController.isEditMode = false;
                MainWindow.window.pushPage("qrc:/qml/page/T_EventoEdit.qml");
            }

            anchors {
                top: parent.top
                topMargin: 10
                right: parent.right
                rightMargin: 10
            }

        }

    }

    Flickable {
        contentHeight: table.height
        contentWidth: table.width
        clip: true

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            rightMargin: 5
            topMargin: 50
            bottomMargin: 5
        }

        FluFrame {
            id: table

            readonly property int blockHeight: 45
            readonly property int blockWidth: (width - 50) / 7
            readonly property int all_day_height: EventoBlockModel.all_day_line_num * blockHeight

            color: "transparent"
            anchors.left: parent.left
            height: 765 + all_day_height
            width: calendar.width > 890 ? calendar.width - 40 : 850

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
                height: table.all_day_height
                width: 50
                text: "Multi\nDay"
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignHCenter
                visible: EventoBlockModel.all_day_line_num

                anchors {
                    top: weekTitle.bottom
                    topMargin: 10
                }

            }

            Repeater {
                model: EventoBlockModel.all_day_line_num

                delegate: FluRectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255, 62 / 255, 1) : "#e1dfdd"

                    anchors {
                        top: weekTitle.bottom
                        topMargin: 10 + index * table.blockHeight
                        left: parent.left
                        leftMargin: 50
                        right: parent.right
                        rightMargin: 10
                    }

                }

            }

            Row {
                spacing: table.blockWidth - 1

                anchors {
                    top: parent.top
                    topMargin: 5
                    left: parent.left
                    leftMargin: 50
                }

                Repeater {
                    model: 7

                    delegate: FluRectangle {
                        width: 1
                        height: table.height - 28
                        color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255, 62 / 255, 1) : "#e1dfdd"
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

                        Layout.fillWidth: true
                        height: 1
                        color: FluTheme.dark ? Qt.rgba(62 / 255, 62 / 255, 62 / 255, 1) : "#e1dfdd"

                        anchors {
                            top: parent.top
                            left: parent.left
                            leftMargin: 50
                            right: parent.right
                            rightMargin: 10
                        }

                    }

                    FluText {
                        text: title
                        font: FluTextStyle.Caption
                        color: FluColors.Grey110
                        horizontalAlignment: Text.AlignHCenter

                        anchors {
                            left: parent.left
                            right: row_line.left
                            verticalCenter: row_line.top
                        }

                    }

                }

            }

            Repeater {
                model: EventoBlockModel

                delegate: FluFrame {
                    readonly property double width_min: table.blockWidth / (depth_max + 1)

                    height: is_all_day ? table.blockHeight : table.blockHeight * (end - start)
                    width: is_all_day ? table.blockWidth * (end - start) : (depth == depth_max ? 1 : 1.618) * width_min
                    color: FluTheme.dark ? Qt.rgba(23 / 255, 49 / 255, 102 / 255, 1) : Qt.rgba(224 / 255, 233 / 255, 255 / 255, 1)

                    anchors {
                        top: weekTitle.bottom
                        topMargin: is_all_day ? 10 + depth * table.blockHeight : 10 + table.all_day_height + start * table.blockHeight
                        left: parent.left
                        leftMargin: is_all_day ? 50 + start * table.blockWidth : 50 + column * table.blockWidth + depth * width_min
                    }

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
                        onClicked: (mouse) => {
                            if (mouse.button === Qt.LeftButton) {
                                EventoHelper.id = id;
                                EventoInfoController.editable = editable;
                                blockWindowLauncher.launch();
                            }
                        }
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: {
                            if (!editable)
                                return FluTheme.dark ? Qt.rgba(33 / 255, 45 / 255, 69 / 255, 0.5) : Qt.rgba(241 / 255, 245 / 255, 255 / 255, 0.5);

                            if (FluTheme.dark) {
                                if (event_mouse.containsMouse)
                                    return Qt.rgba(1, 1, 1, 0.03);

                                return Qt.rgba(0, 0, 0, 0);
                            } else {
                                if (event_mouse.containsMouse)
                                    return Qt.rgba(0, 0, 0, 0.03);

                                return Qt.rgba(0, 0, 0, 0);
                            }
                        }
                    }

                }

            }

        }

        ScrollBar.horizontal: FluScrollBar {
        }

        ScrollBar.vertical: FluScrollBar {
        }

    }

}
