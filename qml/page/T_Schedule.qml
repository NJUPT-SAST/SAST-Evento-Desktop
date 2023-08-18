import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import MyModel
import "../window"

FluScrollablePage {
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
    }

    ListView {
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        spacing: 10
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
            height: 80 + loader.height

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
                        text: "活动标题"
                        font: FluTextStyle.Title
                    }
                    FluText {
                        text: "活动地点"
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
                    color: FluColors.Yellow.normal
                    font.pixelSize: 20
                }

                FluText {
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                        rightMargin: 10
                        bottomMargin: 10
                    }
                    text: "活动部门"
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
                        EventoHelper.id = model.id
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_EventInfo.qml")
                    }
                }
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
                text: "签到"
                font.pixelSize: 16
            }

            state: modelData.state

            states: [
                State {
                    name: 'Before'
                    PropertyChanges {
                        target: event_state
                        text: "未开始"
                        color: FluColors.Yellow.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "签到"
                        disabled: false
                        onClicked: {

                            // TODO
                        }
                    }
                },
                State {
                    name: 'Undertaking'
                    PropertyChanges {
                        target: event_state
                        text: "进行中"
                        color: FluColors.Green.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "签到"
                        disabled: false
                        onClicked: {

                            // TODO
                        }
                    }
                },
                State {
                    name: 'isChecked'
                    PropertyChanges {
                        target: btn
                        text: "已签到"
                        disabled: true
                        onClicked: {

                            // TODO
                        }
                    }
                },
                State {
                    name: 'Cancelled'
                    PropertyChanges {
                        target: event_state
                        text: "已取消"
                        color: FluColors.Grey110
                    }
                    PropertyChanges {
                        target: btn
                        text: ""
                        disabled: true
                    }
                },
                State {
                    name: 'Over'
                    PropertyChanges {
                        target: event_state
                        text: "已结束"
                        color: FluColors.Red.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "评价"
                        disabled: false
                        onClicked: {

                            // TODO
                        }
                    }
                },
                State {
                    name: 'isFeedback'
                    PropertyChanges {
                        target: event_state
                        text: "已结束"
                        color: FluColors.Red.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: "修改评价"
                        disabled: false
                        onClicked: {

                            // TODO
                        }
                    }
                }
            ]
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
                    "state": 'Over',
                    "date": "10月01日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 2,
                    "title": "活动标题",
                    "state": 'Undertaking',
                    "date": "10月01日",
                    "startTime": "12:00",
                    "endTime": "13:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 3,
                    "title": "活动标题",
                    "state": 'isChecked',
                    "date": "10月03日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 4,
                    "title": "活动标题",
                    "state": 'Over',
                    "date": "10月04日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 5,
                    "title": "活动标题",
                    "state": 'isFeedback',
                    "date": "10月04日",
                    "startTime": "15:00",
                    "endTime": "15:30",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 6,
                    "title": "活动标题",
                    "state": 'Over',
                    "date": "10月04日",
                    "startTime": "17:00",
                    "endTime": "19:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }, {
                    "id": 7,
                    "title": "活动标题",
                    "state": 'Cancelled',
                    "date": "10月06日",
                    "startTime": "09:00",
                    "endTime": "10:00",
                    "department": "活动部门",
                    "location": "活动地点"
                }]
    }
}
