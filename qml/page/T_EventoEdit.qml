import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../imports"
import "../window"

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask
    property var locationArr: []
    property var departmentArr: []

    function parseJSON(data) {
        var result = []
        if (Array.isArray(data)) {
            for (var i = 0; i < data.length; i++) {
                var item = data[i]
                var name = item.name
                var isLeaf = false
                var children = []

                if (item.children && Array.isArray(item.children))
                    children = parseJSON(item.children)
                else
                    isLeaf = true

                result.push(tree_view_location.createItem(name, isLeaf,
                                                          children, {
                                                              "id": item.id
                                                          }))
            }
        } else {
            result.push(tree_view_location.createItem(data.name, true, [], {
                                                          "id": data.id
                                                      }))
        }
        return result
    }

    function loadEditInfo() {
        statusMode = FluStatusViewType.Loading
        EventoEditController.loadEditInfo()
    }

    signal listReady

    Component.onCompleted: {
        statusMode = FluStatusViewType.Loading
        loadEditInfo()
    }

    Connections {
        target: EventoEditController
        function onLoadEditSuccessEvent() {
            departmentArr = []
            var json = JSON.parse(EventoEditController.departmentJson)
            for (var ii = 0; ii < json.length; ++ii) {
                departmentArr.push(tree_view_department.createItem(
                                       json[ii].name, true, [], {
                                           "id": json[ii].id
                                       }))
            }
            json = JSON.parse(EventoEditController.locationJson)
            locationArr = parseJSON(json)
            listReady()
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: EventoEditController
        function onLoadEditErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Item {
        id: item_all
        Layout.fillWidth: true
        implicitHeight: 650 + textbox_description.implicitHeight
        FluArea {
            id: area1
            width: parent.width
            height: 255
            anchors {
                top: parent.top
            }
        }
        FluArea {
            id: area2
            width: parent.width
            height: 230
            anchors {
                top: area1.bottom
                topMargin: 10
            }
        }
        FluArea {
            id: area3
            width: parent.width
            height: 65 + textbox_description.implicitHeight
            anchors {
                top: area2.bottom
                topMargin: 10
            }
        }

        // deprecated


        /*
        Item {
            visible: false
            FluArea {
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
            anchors {
                left: item_title.left
                top: item_title.bottom
                topMargin: 15
            }
            text: "标签"
            font.pixelSize: 20
            font.bold: true
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
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.eventStart) : new Date
            anchors {
                left: clender_picker_register_start.left
                top: item_event_time.top
            }
        }
        FluTimePicker {
            id: time_picker_event_start
            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.eventStart) : new Date

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
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.eventEnd) : new Date
            anchors {
                left: clender_picker_register_start.left
                top: text_end2.top
            }
        }
        FluTimePicker {
            id: time_picker_event_end
            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.eventEnd) : new Date
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
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.registerStart) : new Date
            anchors {
                left: text_start1.right
                leftMargin: 18
                top: item_register_time.top
            }
        }
        FluTimePicker {
            id: time_picker_register_start
            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.registerStart) : new Date
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
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.registerEnd) : new Date
            anchors {
                left: clender_picker_register_start.left
                top: text_end1.top
            }
        }
        FluTimePicker {
            id: time_picker_register_end
            hourFormat: FluTimePickerType.HH
            current: EventoEditController.isEditMode ? Date.fromLocaleString(
                                                           EventoEditController.registerEnd) : (new Date)
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

        FluArea {
            id: rect_location
            width: 200
            height: 200
            anchors {
                top: item_location.top
                left: textbox_title.left
            }
            FluTreeView {
                id: tree_view_location
                property int locationId: 0
                width: 200
                height: 200
                selectionMode: FluTreeViewType.Single
                Connections {
                    target: page
                    function onListReady() {
                        tree_view_location.updateData(locationArr)
                    }
                }
                onItemClicked: item => {
                                   locationId = item.data.id
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

        FluArea {
            id: rect_department
            width: 200
            height: 200
            anchors {
                top: item_department.top
                left: item_department.right
                leftMargin: 60
            }
            FluTreeView {
                id: tree_view_department
                width: 200
                height: 200
                selectionMode: FluTreeViewType.Multiple
                Connections {
                    target: page
                    function onListReady() {
                        tree_view_department.updateData(departmentArr)
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
            property int typeId: {
                var idx = find(displayText)
                return idx === -1 ? 0 : model[idx][id]
            }
            width: 200
            anchors {
                left: textbox_tag.left
                top: item_type.top
            }
            model: TypeModel
            textRole: "name"
            displayText: EventoEditController.isEditMode ? textAt(
                                                               EventoEditController.typeId) : ""
        }

        FluText {
            id: item_description
            text: "描述"
            font.pixelSize: 20
            font.bold: true
            anchors {
                left: item_title.left
                top: item_allow_comflict.bottom
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

        // deprecated


        /*
        Item {
            visible: false

            FluText {
                id: item_slide
                text: "图片"
                font.pixelSize: 20
                font.bold: true
                anchors {
                    left: item_title.left
                    top: textbox_description.bottom
                    topMargin: 40
                }
            }
            FluFilledButton {
                id: btn_open_gallery
                text: "打开图库"
                implicitWidth: 200
                anchors {
                    left: textbox_title.left
                    top: item_slide.top
                }
                onClicked: {
                    GalleryHelper.maxNum = 3
                    MainWindow.window.pushPage(
                                "qrc:/qml/page/T_PictureSelection.qml")
                }
            }

            FluText {
                text: "请选择1~3张\n右键图片可删除"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
                anchors {
                    left: item_title.left
                    top: list_view_slide.top
                }
            }

            ListView {
                id: list_view_slide
                width: 600
                height: 150
                orientation: ListView.Horizontal
                spacing: 5
                anchors {
                    left: textbox_title.left
                    top: item_slide.bottom
                    topMargin: 15
                }
                model: GalleryHelper.urlList
                delegate: Component {
                    FluImage {
                        width: 200
                        height: 150
                        source: model.modelData
                        fillMode: Image.PreserveAspectCrop
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.RightButton
                            onClicked: menu.popup()
                        }
                        FluMenu {
                            id: menu
                            FluMenuItem {
                                text: "删除"
                                onClicked: {
                                    GalleryHelper.removeByIndex(model.index)
                                }
                            }
                        }
                    }
                }
            }
        }
        */
        FluButton {
            text: "取消"
            implicitWidth: 100
            implicitHeight: 35
            anchors {
                top: area3.bottom
                topMargin: 10
                right: area3.right
                rightMargin: 110
            }
            onClicked: {
                returnPage()
            }
        }

        FluFilledButton {
            text: EventoEditController.isEditMode ? "完成修改" : "创建"
            implicitWidth: 100
            implicitHeight: 35
            anchors {
                top: area3.bottom
                topMargin: 10
                right: area3.right
            }
            onClicked: {
                var ids = []
                var typeId = combo_box_type.typeId
                ree_view_department.multipData().map(value => ids.push(
                                                         value.data.id))
                if (ids.length === 0 || textbox_title.text === ""
                        || textbox_description.text === "" || typeId === 0
                        || tree_view_location.locationId === 0
                        || textbox_tag.text === "") {
                    showInfo("有信息未填写")
                    return
                }
                statusMode = FluStatusViewType.Loading

                EventoEditController.createEvento(
                            textbox_title.text, textbox_description.text, clender_picker_event_start.text + " " + time_picker_event_start.current.getHours() + ":" + time_picker_event_start.current.getMinutes(
                                ), clender_picker_event_end.text + " " + time_picker_event_end.current.getHours(
                                ) + ":" + time_picker_event_end.current.getMinutes(),
                            clender_picker_register_start.text + " " + time_picker_register_start.current.getHours() + ":" + time_picker_register_start.current.getMinutes(), clender_picker_register_end.text
                            + " " + time_picker_register_end.current.getHours() + ":"
                            + time_picker_register_end.current.getMinutes(), typeId, tree_view_location.locationId,
                            ids, textbox_tag.text)
            }
        }
    }

    function returnPage() {
        MainWindow.window.pushPage("qrc:/qml/page/T_Calendar.qml")
    }

    Connections {
        target: EventoEditController
        function onCreateSuccessEvent() {
            statusMode = FluStatusViewType.Success
            showSuccess("操作成功")
            returnPage()
        }
    }

    Connections {
        target: EventoEditController
        function onCreateErrorEvent(message) {
            statusMode = FluStatusViewType.Success
            showError(message)
        }
    }
}
