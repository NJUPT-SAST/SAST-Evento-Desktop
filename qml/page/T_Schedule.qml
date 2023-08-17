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
        delegate: com_schedule

        Component.onCompleted: {
            model = getEventItems()
        }
    }

    Component {
        id: com_schedule
        Item {
            width: parent.width
            height: 90
            FluArea {
                id: area_content
                width: parent.width - 85
                height: 80

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
                    anchors {
                        left: item_division.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluText {
                        text: "09:00"
                        font.pixelSize: 18
                    }
                    FluText {
                        text: "10:00"
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
                    anchors {
                        right: parent.right
                        top: parent.top
                        topMargin: 10
                        rightMargin: 10
                    }
                    text: "进行中"
                    color: FluColors.Green.normal
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
                    left: area_content.right
                    leftMargin: 5
                }
                height: 80
                width: 75
                text: "签到"
                font.pixelSize: 16
            }
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
