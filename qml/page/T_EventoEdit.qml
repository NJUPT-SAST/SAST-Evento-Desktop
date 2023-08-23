import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    Item {
        Layout.fillWidth: true
        height: 900

        FluText {
            id: item_title
            text: "标题"
            font.pixelSize: 25
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 10
        }
        FluTextBox {
            id: textbox_title
            implicitWidth: 600
            anchors {
                left: item_title.right
                leftMargin: 60
                verticalCenter: item_title.verticalCenter
            }
        }

        FluText {
            id: item_tag
            anchors {
                top: item_title.bottom
                topMargin: 15
            }
            text: "标签"
            font.pixelSize: 25
            font.bold: true
        }
        FluTextBox {
            id: textbox_tag
            implicitWidth: 600
            anchors {
                left: textbox_title.left
                verticalCenter: item_tag.verticalCenter
            }
        }

        ////////////////
        FluText {
            id: item_register_time
            text: "报名时间"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_title.left
                top: item_tag.bottom
                topMargin: 15
            }
        }
        FluText {
            id: text_start1
            text: "开始"
            font.pixelSize: 22
            anchors {
                left: textbox_title.left
                top: item_register_time.top
            }
        }
        FluCalendarPicker {
            id: clender_picker_register_start
            width: 220
            anchors {
                left: text_start1.right
                leftMargin: 20
                top: item_register_time.top
            }
        }
        FluTimePicker {
            id: time_picker_register_start
            hourFormat: FluTimePickerType.HH
            anchors {
                left: clender_picker_register_start.right
                leftMargin: 15
                top: item_register_time.top
            }
        }
        FluText {
            id: text_end1
            text: "结束"
            font.pixelSize: 22
            anchors {
                left: textbox_title.left
                top: text_start1.bottom
                topMargin: 15
            }
        }
        FluCalendarPicker {
            id: clender_picker_register_end
            width: 220
            anchors {
                left: clender_picker_register_start.left
                top: text_end1.top
            }
        }
        FluTimePicker {
            id: time_picker_register_end
            hourFormat: FluTimePickerType.HH
            anchors {
                left: time_picker_register_start.left
                top: text_end1.top
            }
        }
        ////////////////
        FluText {
            id: item_event_time
            text: "活动时间"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_title.left
                top: text_end1.bottom
                topMargin: 15
            }
        }
        FluText {
            id: text_start2
            text: "开始"
            font.pixelSize: 22
            anchors {
                left: textbox_title.left
                top: item_event_time.top
            }
        }
        FluCalendarPicker {
            id: clender_picker_event_start
            width: 220
            anchors {
                left: clender_picker_register_start.left
                top: item_event_time.top
            }
        }
        FluTimePicker {
            id: time_picker_evnet_start
            hourFormat: FluTimePickerType.HH
            anchors {
                left: time_picker_register_start.left
                top: item_event_time.top
            }
        }
        FluText {
            id: text_end2
            text: "结束"
            font.pixelSize: 22
            anchors {
                left: textbox_title.left
                top: text_start2.bottom
                topMargin: 15
            }
        }
        FluCalendarPicker {
            id: clender_picker_event_end
            width: 220
            anchors {
                left: clender_picker_register_start.left
                top: text_end2.top
            }
        }
        FluTimePicker {
            id: time_picker_event_end
            hourFormat: FluTimePickerType.HH
            anchors {
                left: time_picker_register_start.left
                top: text_end2.top
            }
        }

        ////////////////
        FluText {
            id: item_location
            text: "地点"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_title.left
                top: text_end2.bottom
                topMargin: 15
            }
        }

        FluRectangle {
            id: rect_location
            width: 200
            height: 200
            radius: [3, 3, 3, 3]
            anchors {
                top: item_location.top
                left: textbox_title.left
            }
            FluTreeView {
                id: tree_view_location
                width: 200
                height: 200
                selectionMode: FluTreeViewType.Single

                Component.onCompleted: {
                    var arr = []
                    arr.push(createItem('location1', true))
                    arr.push(createItem('location2', true))
                    arr.push(createItem('location3', true))
                    arr.push(createItem('location4', true))
                    arr.push(createItem('location5', true))
                    arr.push(createItem('location6', true))
                    arr.push(createItem('location7', true))
                    // TODO
                    updateData(arr)
                }
            }
        }

        FluText {
            id: item_department
            text: "部门"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: rect_location.right
                top: item_location.top
                leftMargin: 90
            }
        }

        FluRectangle {
            id: rect_department
            width: 200
            height: 200
            radius: [3, 3, 3, 3]
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

                Component.onCompleted: {
                    var arr = []
                    arr.push(createItem('department1', true))
                    arr.push(createItem('department2', true))
                    arr.push(createItem('department3', true))
                    arr.push(createItem('department4', true))
                    arr.push(createItem('department5', true))
                    arr.push(createItem('department6', true))
                    arr.push(createItem('department7', true))
                    // TODO
                    updateData(arr)
                }
            }
        }

        FluText {
            id: item_type
            text: "类型"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_title.left
                top: rect_location.bottom
                topMargin: 15
            }
        }
        FluComboBox {
            id: combo_box_type
            width: 200
            anchors {
                left: textbox_tag.left
                top: item_type.top
            }
        }

        FluText {
            id: item_allow_comflict
            text: "允许冲突"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_department.left
                top: item_type.top
            }
        }
        FluCheckBox {
            id: check_box_allow
            anchors {
                left: rect_department.left
                bottom: item_allow_comflict.bottom
            }
        }

        FluText {
            id: item_description
            text: "描述"
            font.pixelSize: 25
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
            anchors {
                left: textbox_title.left
                top: item_description.top
            }
        }

        FluText {
            id: item_slide
            text: "图片"
            font.pixelSize: 25
            font.bold: true
            anchors {
                left: item_title.left
                top: item_description.bottom
                topMargin: 15
            }
        }
        FluFilledButton {
            id: btn_open_gallery
            text: "打开图库"
            anchors {
                left: textbox_title.left
                top: item_slide.top
            }
            onClicked: {

                //TODO
            }
        }

        FluText {
            text: "请选择1~3张\n右键图片可删除"
            font: FluTextStyle.Caption
            color: FluColors.Grey110
            anchors {
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

            model: [{
                    "id": 1,
                    "url": "qrc:/res/image/banner_1.png"
                }, {
                    "id": 2,
                    "url": "qrc:/res/image/banner_2.png"
                }, {
                    "id": 3,
                    "url": "qrc:/res/image/banner_3.png"
                }]

            delegate: Component {
                FluImage {
                    width: 200
                    height: 150
                    source: modelData.url
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

                                // TODO
                            }
                        }
                    }
                }
            }
        }

        FluFilledButton {
            text: "创建"
            implicitWidth: 120
            anchors {
                bottom: parent.bottom
                bottomMargin: 15
                right: textbox_title.right
            }
        }
    }
}