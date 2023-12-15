import QtQuick
import QtQuick.Controls
import FluentUI
import SAST_Evento

FluScrollablePage {
    id: calendar
    launchMode: FluPageType.SingleTask

    Rectangle {
        id: lesson_pic
        width: 1080
        height: 1920 + (lesson_detail.num - 2) * 430
        color: "#EAEAEA"

        Image {
            id: bg_image
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }

            Text {
                id: dep_title
                anchors {
                    top: parent.top
                    topMargin: 196
                    left: parent.left
                    leftMargin: 90
                }

                text: qsTr("%1").arg(dep_name)
                font.pixelSize: 90
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop

                property string dep_name: "软研"
            }

            Text {
                id: week_title
                anchors {
                    top: dep_title.bottom
                    left: dep_title.left
                }

                text: qsTr("第%1周").arg(week_num)
                font.pixelSize: 90
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.bold: true

                property int week_num: 15
            }

            Text {
                id: title_txt
                anchors {
                    top: week_title.bottom
                    left: dep_title.left
                }

                text: qsTr("授课课表")
                font.pixelSize: 90
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.bold: true
            }

            source: "qrc:/res/image/department/SRD_lesson_pic_bg.jpg"
            fillMode: Image.PreserveAspectFit
        }

        Column {
            anchors {
                top: bg_image.bottom
                topMargin: 100
                left: parent.left
                leftMargin: 50
                right: parent.right
            }

            spacing: 100

            Repeater {
                id: lesson_detail
                property int num: 2
                property var dep: ["C++", "软件研发中心"]

                model: num
                delegate: Rectangle {
                    height: 330
                    anchors {
                        left: parent.left
                        right: parent.right
                        rightMargin: 100
                    }

                    Rectangle {
                        id: dep_title_block_rect
                        height: 100
                        anchors {
                            left: parent.left
                            leftMargin: 50
                            right: dep_title_block.right
                        }
                        color: "#fed547"
                    }

                    Row {
                        id: dep_title_block
                        anchors {
                            left: parent.left
                            leftMargin: 60
                        }

                        Image {
                            anchors {
                                top: parent.top
                                topMargin: 5
                                bottom: parent.bottom
                                bottomMargin: 5
                            }
                            source: "qrc:/res/image/department/cpp_1.svg"
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            leftPadding: 20
                            rightPadding: 40
                            height: dep_title_block_rect.height
                            text: lesson_detail.dep[index]
                            font.pixelSize: 50
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true
                        }
                    }

                    Text {
                        id: txt
                        anchors {
                            top: dep_title_block_rect.bottom
                            topMargin: 20
                            left: dep_title_block_rect.left
                            right: parent.right
                            bottom: parent.bottom
                        }
                        text: qsTr("%1").arg(index)
                    }
                }
            }
        }
    }
}
