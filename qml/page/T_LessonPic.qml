import QtQuick
import QtQuick.Controls
import FluentUI
import SAST_Evento

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask

    Rectangle {
        id: lesson_pic
        height: 660 + LessonModel.rowCount() * 430
        width: 1080
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

                model: LessonModel
                delegate: Item {
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
                            source: icon
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            leftPadding: 20
                            rightPadding: 40
                            height: dep_title_block_rect.height
                            text: title
                            font.pixelSize: 50
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true
                        }
                    }

                    Text {
                        id: time_txt
                        anchors {
                            top: dep_title_block_rect.bottom
                            topMargin: 20
                            left: dep_title_block_rect.left
                            right: parent.right
                        }
                        text: qsTr("时间：%1").arg(time)
                        font.pixelSize: 36
                    }

                    Text {
                        id: loc_txt
                        anchors {
                            top: time_txt.bottom
                            topMargin: 10
                            left: dep_title_block_rect.left
                            right: parent.right
                        }
                        text: qsTr("地点：%1").arg(loc)
                        font.pixelSize: 36
                    }

                    Text {
                        id: topic_txt
                        anchors {
                            top: loc_txt.bottom
                            topMargin: 10
                            left: dep_title_block_rect.left
                            right: parent.right
                        }
                        text: qsTr("主题：%1").arg(topic)
                        font.pixelSize: 36
                    }
                }
            }
        }
    }
}
