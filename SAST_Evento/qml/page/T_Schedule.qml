import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/global"

FluScrollablePage {

    title: lang.lang_schedule
    launchMode: FluPageType.SingleTask

    ColumnLayout {
        Layout.topMargin: 10
        Layout.fillWidth: true

        Component {
            id: com_item
            Item {
                Layout.topMargin: 10
                width: parent.width
                height: 110
                FluArea {
                    radius: 8
                    width: parent.width
                    height: 100
                    anchors.centerIn: parent
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
                    FluRectangle {
                        id: item_icon
                        height: 80
                        width: 80
                        radius: [6, 6, 6, 6]
                        anchors {
                            left: parent.left
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        FluImage {
                            anchors.fill: parent
                            source: modelData.image
                            fillMode: Image.PreserveAspectCrop
                        }
                    }

                    FluText {
                        id: item_title
                        text: modelData.title
                        font: FluTextStyle.Title
                        anchors {
                            left: item_icon.right
                            leftMargin: 20
                            top: item_icon.top
                        }
                    }

                    FluText {
                        id: item_time
                        text: modelData.time
                        color: FluColors.Grey120
                        wrapMode: Text.WordWrap
                        font: FluTextStyle.Caption
                        anchors {
                            left: item_title.left
                            right: parent.right
                            rightMargin: 20
                            top: item_title.bottom
                            topMargin: 3
                        }
                    }

                    FluText {
                        id: item_status
                        wrapMode: Text.WordWrap
                        font: FluTextStyle.Body
                        anchors {
                            left: item_title.left
                            right: parent.right
                            rightMargin: 20
                            bottom: parent.bottom
                            bottomMargin: 15
                        }

                        Loader {
                            id: loader
                            anchors {
                                right: parent.right
                            }
                        }

                        Component {
                            id: inProgress
                            FluTextButton {
                                text: lang.lang_check
                                onClicked: {
                                    text = lang.lang_checked
                                    showSuccess("签到成功")
                                    disabled = true
                                }
                            }
                        }

                        Component {
                            id: finished
                            FluTextButton {
                                text: lang.lang_comment
                                onClicked: {
                                    ItemsOriginal.item.navigationView.push(
                                                "qrc:/SAST_Evento/qml/page/T_EventInfo.qml")
                                }
                            }
                        }

                        Component.onCompleted: {
                            if (modelData.id % 3 === 0) {
                                text = lang.lang_undertaking
                                color = "#107C10"
                                loader.sourceComponent = inProgress
                            } else if (modelData.id % 3 === 1) {
                                text = lang.lang_not_started
                                color = "#0078D4"
                            } else {
                                text = lang.lang_over
                                color = FluColors.Grey120
                                loader.sourceComponent = finished
                            }
                        }
                    }

                    MouseArea {
                        id: item_mouse
                        anchors {
                            fill: parent
                            rightMargin: 80
                        }

                        hoverEnabled: true
                        onClicked: {
                            ItemsOriginal.item.navigationView.push(
                                        "qrc:/SAST_Evento/qml/page/T_EventInfo.qml")
                        }
                    }
                }
            }
        }

        ListView {
            Layout.fillWidth: true
            implicitHeight: contentHeight
            interactive: false
            delegate: com_item

            Component.onCompleted: {
                model = getEventItems()
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
