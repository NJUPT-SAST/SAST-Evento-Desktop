import "../component"
import "../page"
import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollableStatusPage {
    id: page

    function loadEditInfo() {
        statusMode = FluStatusLayoutType.Loading;
        EventoEditController.loadEditInfo();
    }

    function returnPage() {
        control.load();
        MainWindow.window.pushPage("qrc:/qml/page/T_Calendar.qml");
    }

    launchMode: FluPageType.SingleTask
    onErrorClicked: {
        loadEditInfo();
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Connections {
        function onLoadEditSuccessEvent() {
            statusMode = FluStatusLayoutType.Success;
        }

        target: EventoEditController
    }

    Connections {
        function onLoadEditErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: EventoEditController
    }

    Connections {
        function onCreateSuccessEvent() {
            statusMode = FluStatusLayoutType.Success;
            showSuccess("操作成功");
            returnPage();
        }

        target: EventoEditController
    }

    Connections {
        function onCreateErrorEvent(message) {
            statusMode = FluStatusLayoutType.Success;
            showError(message, 4000);
        }

        target: EventoEditController
    }

    Item {
        // deprecated
        //        Item {
        //            visible: false
        //            FluText {
        //                id: item_slide
        //                text: "图片"
        //                font.pixelSize: 20
        //                font.bold: true
        //                anchors {
        //                    left: item_title.left
        //                    top: textbox_description.bottom
        //                    topMargin: 40
        //                }
        //            }
        //            FluFilledButton {
        //                id: btn_open_gallery
        //                text: "打开图库"
        //                implicitWidth: 200
        //                anchors {
        //                    left: textbox_title.left
        //                    top: item_slide.top
        //                }
        //                onClicked: {
        //                    GalleryHelper.maxNum = 3
        //                    MainWindow.window.pushPage(
        //                                "qrc:/qml/page/T_PictureSelection.qml")
        //                }
        //            }
        //            FluText {
        //                text: "请选择1~3张\n右键图片可删除"
        //                font: FluTextStyle.Caption
        //                color: FluColors.Grey110
        //                anchors {
        //                    left: item_title.left
        //                    top: list_view_slide.top
        //                }
        //            }
        //            ListView {
        //                id: list_view_slide
        //                width: 600
        //                height: 150
        //                orientation: ListView.Horizontal
        //                spacing: 5
        //                anchors {
        //                    left: textbox_title.left
        //                    top: item_slide.bottom
        //                    topMargin: 15
        //                }
        //                model: GalleryHelper.urlList
        //                delegate: Component {
        //                    FluImage {
        //                        width: 200
        //                        height: 150
        //                        source: model.modelData
        //                        fillMode: Image.PreserveAspectCrop
        //                        MouseArea {
        //                            anchors.fill: parent
        //                            acceptedButtons: Qt.RightButton
        //                            onClicked: menu.popup()
        //                        }
        //                        FluMenu {
        //                            id: menu
        //                            FluMenuItem {
        //                                text: "删除"
        //                                onClicked: {
        //                                    GalleryHelper.removeByIndex(model.index)
        //                                }
        //                            }
        //                        }
        //                    }
        //                }
        //            }
        //        }

        id: item_all

        Layout.fillWidth: true
        implicitHeight: 650 + textbox_description.implicitHeight
        Component.onCompleted: {
            loadEditInfo();
        }

        FluFrame {
            id: area1

            width: parent.width
            height: 255

            anchors {
                top: parent.top
            }

        }

        FluFrame {
            id: area2

            width: parent.width
            height: 230

            anchors {
                top: area1.bottom
                topMargin: 10
            }

        }

        FluFrame {
            id: area3

            width: parent.width
            height: 80 + textbox_description.implicitHeight

            anchors {
                top: area2.bottom
                topMargin: 10
            }

        }

        /*
        Item {
            visible: false
            FluFrame {
                id: area4
                width: parent.width
                height: 230
                anchors {
                    top: area3.bottom
                    topMargin: 10
                }
            }
        }
        */
        FluText {
            id: item_title

            text: "标题"
            font.pixelSize: 20
            font.bold: true

            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 20
            }

        }

        FluTextBox {
            id: textbox_title

            implicitWidth: 600
            text: EventoEditController.isEditMode ? EventoHelper.title : ""

            anchors {
                left: item_title.right
                leftMargin: 60
                verticalCenter: item_title.verticalCenter
            }

        }

        FluText {
            id: item_tag

            text: "标签"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: item_title.bottom
                topMargin: 15
            }

        }

        FluTextBox {
            id: textbox_tag

            implicitWidth: 600
            text: EventoEditController.isEditMode ? EventoHelper.tag : ""

            anchors {
                left: textbox_title.left
                verticalCenter: item_tag.verticalCenter
            }

        }

        FluText {
            id: item_event_time

            text: "活动时间"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: item_tag.bottom
                topMargin: 15
            }

        }

        FluText {
            id: text_start2

            text: "开始"
            font.pixelSize: 18

            anchors {
                left: textbox_title.left
                top: item_event_time.top
            }

        }

        FluCalendarPicker {
            id: clender_picker_event_start

            width: 220
            current: EventoEditController.isEditMode ? new Date(EventoEditController.eventStart) : new Date

            anchors {
                left: clender_picker_register_start.left
                top: item_event_time.top
            }

        }

        FluTimePicker {
            id: time_picker_event_start

            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? new Date(EventoEditController.eventStart) : new Date

            anchors {
                left: time_picker_register_start.left
                top: item_event_time.top
            }

        }

        FluText {
            id: text_end2

            text: "结束"
            font.pixelSize: 18

            anchors {
                left: textbox_title.left
                top: text_start2.bottom
                topMargin: 15
            }

        }

        FluCalendarPicker {
            id: clender_picker_event_end

            width: 220
            current: EventoEditController.isEditMode ? new Date(EventoEditController.eventEnd) : new Date

            anchors {
                left: clender_picker_register_start.left
                top: text_end2.top
            }

        }

        FluTimePicker {
            id: time_picker_event_end

            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? new Date(EventoEditController.eventEnd) : new Date

            anchors {
                left: time_picker_register_start.left
                top: text_end2.top
            }

        }

        FluText {
            id: item_register_time

            text: "报名时间"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: clender_picker_event_end.bottom
                topMargin: 15
            }

        }

        FluText {
            id: text_start1

            text: "开始"
            font.pixelSize: 20

            anchors {
                left: textbox_title.left
                top: item_register_time.top
            }

        }

        FluCalendarPicker {
            id: clender_picker_register_start

            width: 220
            current: EventoEditController.isEditMode ? new Date(EventoEditController.registerStart) : new Date

            anchors {
                left: text_start1.right
                leftMargin: 18
                top: item_register_time.top
            }

        }

        FluTimePicker {
            id: time_picker_register_start

            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? new Date(EventoEditController.registerStart) : new Date

            anchors {
                left: clender_picker_register_start.right
                leftMargin: 15
                top: item_register_time.top
            }

        }

        FluText {
            id: text_end1

            text: "结束"
            font.pixelSize: 18

            anchors {
                left: textbox_title.left
                top: text_start1.bottom
                topMargin: 15
            }

        }

        FluCalendarPicker {
            id: clender_picker_register_end

            width: 220
            current: EventoEditController.isEditMode ? new Date(EventoEditController.registerEnd) : new Date

            anchors {
                left: clender_picker_register_start.left
                top: text_end1.top
            }

        }

        FluTimePicker {
            id: time_picker_register_end

            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? new Date(EventoEditController.registerEnd) : (new Date)

            anchors {
                left: time_picker_register_start.left
                top: text_end1.top
            }

        }

        FluText {
            id: item_location

            text: "地点"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: text_end1.bottom
                topMargin: 40
            }

        }

        FluFrame {
            id: rect_location

            width: 200
            height: 200
            padding: 10

            anchors {
                top: item_location.top
                left: textbox_title.left
            }

            ListView {
                id: location_view

                anchors.fill: parent
                clip: true

                model: DelegateModel {
                    id: delegate

                    model: LocationModel

                    delegate: Item {
                        id: area

                        height: 40
                        width: 180

                        FluRectangle {
                            id: rect_division

                            width: 6
                            height: 30
                            radius: [3, 3, 3, 3]
                            color: model.id == LocationModel.selected ? FluTheme.primaryColor : FluColors.Grey110

                            anchors {
                                left: parent.left
                                leftMargin: 5 + depth * 10
                                verticalCenter: parent.verticalCenter
                            }

                        }

                        FluText {
                            text: title
                            font.pixelSize: 20

                            anchors {
                                left: rect_division.right
                                leftMargin: 5
                                verticalCenter: parent.verticalCenter
                            }

                        }

                        MouseArea {
                            id: item_mouse

                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                LocationModel.click(delegate.modelIndex(index));
                            }
                        }

                        Rectangle {
                            anchors.fill: parent
                            radius: 8
                            color: {
                                if (FluTheme.dark) {
                                    if (item_mouse.containsMouse)
                                        return Qt.rgba(1, 1, 1, 0.03);

                                    return Qt.rgba(0, 0, 0, 0);
                                } else {
                                    if (item_mouse.containsMouse)
                                        return Qt.rgba(0, 0, 0, 0.03);

                                    return Qt.rgba(0, 0, 0, 0);
                                }
                            }
                        }

                    }

                }

            }

        }

        FluText {
            id: item_department

            text: "部门"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: rect_location.right
                top: item_location.top
                leftMargin: 90
            }

        }

        FluFrame {
            id: rect_department

            property var departmentIds: EventoEditController.isEditMode ? JSON.parse(EventoEditController.departmentIds) : []

            width: 200
            height: 200
            padding: 10

            anchors {
                top: item_department.top
                left: item_department.right
                leftMargin: 60
            }

            ListView {
                clip: true
                anchors.fill: parent
                model: DepartmentModel
                delegate: com_tree_item
            }

            Component {
                id: com_tree_item

                Item {
                    id: area

                    property bool checked: rect_department.departmentIds.indexOf(model.id) >= 0

                    height: 40
                    width: 180

                    FluRectangle {
                        id: rect_division

                        width: 6
                        height: 30
                        radius: [3, 3, 3, 3]
                        color: rect_department.departmentIds.indexOf(model.id) < 0 ? FluColors.Grey110 : FluTheme.primaryColor

                        anchors {
                            leftMargin: 5
                            verticalCenter: parent.verticalCenter
                        }

                    }

                    FluText {
                        text: model.title
                        font.pixelSize: 20

                        anchors {
                            left: rect_division.right
                            leftMargin: 5
                            verticalCenter: parent.verticalCenter
                        }

                    }

                    MouseArea {
                        id: item_mouse

                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            if (!checked)
                                rect_department.departmentIds.push(model.id);
                            else
                                rect_department.departmentIds.splice(rect_department.departmentIds.indexOf(model.id), 1);
                            rect_division.color = rect_department.departmentIds.indexOf(model.id) < 0 ? FluColors.Grey110 : FluTheme.primaryColor;
                            area.checked = !area.checked;
                        }
                    }

                    Rectangle {
                        anchors.fill: parent
                        radius: 8
                        color: {
                            if (FluTheme.dark) {
                                if (item_mouse.containsMouse)
                                    return Qt.rgba(1, 1, 1, 0.03);

                                return Qt.rgba(0, 0, 0, 0);
                            } else {
                                if (item_mouse.containsMouse)
                                    return Qt.rgba(0, 0, 0, 0.03);

                                return Qt.rgba(0, 0, 0, 0);
                            }
                        }
                    }

                }

            }

        }

        FluText {
            id: item_type

            text: "类型"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: rect_location.bottom
                topMargin: 40
            }

        }

        FluComboBox {
            id: combo_box_type

            width: 200
            model: TypeModel
            textRole: "name"
            currentIndex: EventoEditController.isEditMode ? EventoEditController.index : -1

            anchors {
                left: textbox_tag.left
                top: item_type.top
            }

        }

        FluText {
            id: item_description

            text: "描述"
            font.pixelSize: 20
            font.bold: true

            anchors {
                left: item_title.left
                top: combo_box_type.bottom
                topMargin: 15
            }

        }

        FluMultilineTextBox {
            id: textbox_description

            width: 600
            placeholderText: "Ctrl+Enter换行"
            text: EventoEditController.isEditMode ? EventoHelper.description : ""

            anchors {
                left: textbox_title.left
                top: item_description.top
            }

        }

        FluButton {
            text: "取消"
            implicitWidth: 100
            implicitHeight: 35
            onClicked: {
                returnPage();
            }

            anchors {
                top: area3.bottom
                topMargin: 10
                right: area3.right
                rightMargin: 110
            }

        }

        FluFilledButton {
            function format(date, time) {
                return date.getFullYear() + "-" + (date.getMonth() + 1) + "-" + date.getDate() + " " + time.getHours() + ":" + time.getMinutes();
            }

            text: EventoEditController.isEditMode ? "完成修改" : "创建"
            implicitWidth: 100
            implicitHeight: 35
            onClicked: {
                EventoEditController.index = combo_box_type.find(combo_box_type.displayText);
                if (rect_department.departmentIds.length === 0 || textbox_title.text === "" || textbox_description.text === "" || LocationModel.selected === -1 || EventoEditController.index < 0 || textbox_tag.text === "") {
                    showInfo("有信息未填写");
                    return ;
                }
                statusMode = FluStatusLayoutType.Loading;
                EventoEditController.createEvento(textbox_title.text, textbox_description.text, format(clender_picker_event_start.current, time_picker_event_start.current), format(clender_picker_event_end.current, time_picker_event_end.current), format(clender_picker_register_start.current, time_picker_register_start.current), format(clender_picker_register_end.current, time_picker_register_end.current), EventoEditController.index, LocationModel.selected, rect_department.departmentIds, textbox_tag.text);
            }

            anchors {
                top: area3.bottom
                topMargin: 10
                right: area3.right
            }

        }

    }

    T_Calendar {
        id: control
    }

}
