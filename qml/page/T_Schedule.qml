import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import Qt5Compat.GraphicalEffects
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: page
    title: lang.lang_schedule
    launchMode: FluPageType.SingleTask
    property var arr: []

    onErrorClicked: {
        loadScheduleInfo()
    }

    function loadScheduleInfo() {
        statusMode = FluStatusViewType.Loading
        controller.loadSchedule()
    }

    Component.onCompleted: {
        loadScheduleInfo()
    }

    ScheduleController {
        id: controller
        onLoadScheduleSuccessEvent: {
            statusMode = FluStatusViewType.Success
        }
        onLoadScheduleErrorEvent: message => {
                                      errorText = message
                                      statusMode = FluStatusViewType.Error
                                  }
        onCheckSuccessEvent: {
            statusMode = FluStatusViewType.Success
            showSuccess("签到成功")
            loadScheduleInfo()
        }
        onCheckErrorEvent: message => {
                               showError("错误：" + message)
                               loadScheduleInfo()
                           }
    }

    ListView {
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        spacing: 5
        //model: ScheduledEventoModel
        Component.onCompleted: {
            model = getModel()
        }
        delegate: com_schedule
    }

    Component {
        id: com_schedule
        Item {
            property bool _hasSameDate: hasSameDate(modelData.date)
            width: parent.width
            height: 85 + loader.height

            Loader {
                id: loader
                height: _hasSameDate ? 0 : 20
                anchors {
                    left: parent.left
                    leftMargin: 10
                }
                sourceComponent: _hasSameDate ? undefined : com_date
            }

            Component {
                id: com_date
                FluText {
                    text: modelData.date
                    font.pixelSize: 18
                }
            }

            FluArea {
                id: area_content
                width: parent.width - 85
                height: 80
                anchors {
                    top: loader.bottom
                    topMargin: 5
                }

                FluRectangle {
                    id: item_division
                    width: 6
                    height: 60
                    radius: [3, 3, 3, 3]
                    shadow: false
                    color: FluTheme.primaryColor.normal
                    anchors {
                        left: parent.left
                        leftMargin: 5
                        verticalCenter: parent.verticalCenter
                    }
                }

                Column {
                    id: item_time
                    spacing: 5
                    anchors {
                        left: item_division.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluText {
                        text: modelData.startTime
                        font.pixelSize: 18
                    }
                    FluText {
                        text: modelData.endTime
                        font.pixelSize: 18
                        color: "#708090"
                    }
                }

                FluRectangle {
                    id: item_dot
                    anchors {
                        left: item_time.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    width: 6
                    height: 6
                    radius: [3, 3, 3, 3]
                    shadow: false
                    color: FluColors.Orange.normal
                }

                Column {
                    spacing: 5
                    anchors {
                        left: item_dot.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluText {
                        text: modelData.title
                        font: FluTextStyle.Title
                    }
                    FluText {
                        text: modelData.location
                        font: FluTextStyle.Caption
                        color: FluColors.Grey110
                    }
                }

                FluText {
                    id: event_state
                    anchors {
                        right: parent.right
                        top: parent.top
                        topMargin: 10
                        rightMargin: 10
                    }
                    text: "未开始"
                    color: FluColors.Blue.normal
                    font.pixelSize: 20
                }

                FluText {
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                        rightMargin: 10
                        bottomMargin: 10
                    }
                    text: modelData.department
                    font: FluTextStyle.Caption
                    color: FluColors.Grey110
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
                    onClicked: {
                        EventoHelper.id = modelData.id
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_EventInfo.qml")
                    }
                }
            }

            Component.onCompleted: {
                var modelState = modelData.state
                var isChecked = modelData.isChecked
                var isFeedback = modelData.isFeedback
                if (modelState === 1 || modelState === 2) {
                    if (isChecked)
                        state = 'BeforeAndIsChecked'
                    else
                        state = 'BeforeAndNoChecked'
                } else if (modelState === 3) {
                    if (isChecked)
                        state = 'UndertakingAndIsChecked'
                    else
                        state = 'UndertakingAndNoChecked'
                } else if (modelState === 4)
                    state = 'Cancelled'
                else if (isFeedback)
                    state = 'OverAndIsFeedback'
                else
                    state = 'OverAndNoFeedback'
            }

            FluFilledButton {
                id: btn
                anchors {
                    top: area_content.top
                    left: area_content.right
                    leftMargin: 5
                }
                height: 80
                width: 75
                text: ""
                font.pixelSize: 16
            }

            states: [
                State {
                    name: 'BeforeAndNoChecked'
                    PropertyChanges {
                        target: event_state
                        text: "未开始"
                        color: FluColors.Blue.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "签到"
                        disabled: false
                        onClicked: {
                            dialog.open()
                        }
                    }
                },
                State {
                    name: 'BeforeAndIsChecked'
                    PropertyChanges {
                        target: event_state
                        text: "未开始"
                        color: FluColors.Blue.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "已签到"
                        disabled: true
                    }
                },
                State {
                    name: 'UndertakingAndNoChecked'
                    PropertyChanges {
                        target: event_state
                        text: "进行中"
                        color: FluColors.Orange.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "签到"
                        disabled: false
                        onClicked: {
                            dialog.open()
                        }
                    }
                },
                State {
                    name: 'UndertakingAndIsChecked'
                    PropertyChanges {
                        target: event_state
                        text: "进行中"
                        color: FluColors.Orange.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "已签到"
                        disabled: true
                    }
                },
                State {
                    name: 'Cancelled'
                    PropertyChanges {
                        target: event_state
                        text: "已取消"
                        color: FluColors.Red.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: ""
                        disabled: true
                    }
                },
                State {
                    name: 'OverAndNoFeedback'
                    PropertyChanges {
                        target: event_state
                        text: "已结束"
                        color: FluColors.Grey110
                    }
                    PropertyChanges {
                        target: btn
                        text: "评价"
                        disabled: false
                        onClicked: {
                            EventoHelper.id = modelData.id
                            MainWindow.window.pushPage(
                                        "qrc:/qml/page/T_EventInfo.qml")
                        }
                    }
                },
                State {
                    name: 'OverAndIsFeedback'
                    PropertyChanges {
                        target: event_state
                        text: "已结束"
                        color: FluColors.Grey110
                    }
                    PropertyChanges {
                        target: btn
                        text: "修改评价"
                        disabled: false
                        onClicked: {
                            EventoHelper.id = modelData.id
                            MainWindow.window.pushPage(
                                        "qrc:/qml/page/T_EventInfo.qml")
                        }
                    }
                }
            ]

            FluContentDialog {
                id: dialog
                title: ""
                message: "使用小程序扫描二维码或输入密钥"
                negativeText: "取消"

                Item {
                    anchors {
                        left: parent.left
                        top: parent.top
                        leftMargin: parent.width / 2 - 175
                        topMargin: parent.height / 2 - 60
                    }

                    FluTextBox {
                        id: textbox
                        width: 350
                        placeholderText: "密钥请向讲师获取哦"
                    }
                }

                buttonFlags: FluContentDialogType.NegativeButton
                             | FluContentDialogType.PositiveButton
                positiveText: "签到"
                onPositiveClicked: {
                    if (textbox.text === "") {
                        showError("输入为空")
                        dialog.open()
                    } else {
                        statusMode = FluStatusViewType.Loading
                        controller.check(modelData.id, textbox.text)
                    }
                }
            }
        }
    }

    function hasSameDate(date) {
        if (arr.indexOf(date) > -1)
            return true
        arr.push(date)
        return false
    }

    function getModel() {
        return [{
                    "id": 1,
                    "title": "活动标题",
                    "state": 5,
                    "date": "10月01日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": true,
                    "isFeedback": false
                }, {
                    "id": 2,
                    "title": "活动标题",
                    "state": 3,
                    "date": "10月01日",
                    "startTime": "12:00",
                    "endTime": "13:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": true,
                    "isFeedback": false
                }, {
                    "id": 3,
                    "title": "活动标题",
                    "state": 1,
                    "date": "10月03日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": false,
                    "isFeedback": false
                }, {
                    "id": 4,
                    "title": "活动标题",
                    "state": 5,
                    "date": "10月04日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": true,
                    "isFeedback": false
                }, {
                    "id": 1,
                    "title": "活动标题",
                    "state": 5,
                    "date": "10月04日",
                    "startTime": "15:00",
                    "endTime": "15:30",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": true,
                    "isFeedback": true
                }, {
                    "id": 2,
                    "title": "活动标题",
                    "state": 5,
                    "date": "10月04日",
                    "startTime": "17:00",
                    "endTime": "19:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": true,
                    "isFeedback": false
                }, {
                    "id": 3,
                    "title": "活动标题",
                    "state": 4,
                    "date": "10月06日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点",
                    "isChecked": false,
                    "isFeedback": false
                }]
    }
}
