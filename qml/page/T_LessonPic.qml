import "../component"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import SAST_Evento

FluScrollableStatusPage {
    id: page

    launchMode: FluPageType.SingleTask

    Rectangle {
        id: lesson_pic

        height: 660 + LessonModel.rowCount() * 400
        width: 880
        color: "#EAEAEA"

        Image {
            id: bg_image

            source: "qrc:/res/image/department/SRD_lesson_pic_bg.jpg"
            fillMode: Image.PreserveAspectFit

            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }

            Text {
                id: dep_title

                property string dep_name: "软研"

                text: qsTr("%1").arg(dep_name)
                font.pixelSize: 78
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop

                anchors {
                    top: parent.top
                    topMargin: 175
                    left: parent.left
                    leftMargin: 90
                }

            }

            Text {
                id: week_title

                property int week_num: 15

                text: qsTr("第%1周").arg(week_num)
                font.pixelSize: 78
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.bold: true

                anchors {
                    top: dep_title.bottom
                    left: dep_title.left
                }

            }

            Text {
                id: title_txt

                text: qsTr("授课课表")
                font.pixelSize: 78
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.bold: true

                anchors {
                    top: week_title.bottom
                    left: dep_title.left
                }

            }

            Button {
                id: save_btn

                height: 30
                width: 90
                text: "保存"
                onClicked: {
                    visible = false;
                    file_dialog.open();
                }

                anchors {
                    right: parent.right
                }

                FileDialog {
                    id: file_dialog

                    visible: false
                    nameFilters: ["Image(*.png)"]
                    fileMode: FileDialog.SaveFile
                    onAccepted: {
                        lesson_pic.grabToImage(function(result) {
                            result.saveToFile(file_dialog.selectedFile.toString());
                            save_btn.visible = true;
                        });
                    }
                }

            }

        }

        Column {
            spacing: 80

            anchors {
                top: bg_image.bottom
                topMargin: 100
                left: parent.left
                leftMargin: 50
                right: parent.right
            }

            Repeater {
                model: LessonModel

                delegate: Item {
                    height: 320

                    anchors {
                        left: parent.left
                        right: parent.right
                        rightMargin: 100
                    }

                    Rectangle {
                        id: dep_title_block_rect

                        height: 100
                        color: "#fed547"

                        anchors {
                            left: parent.left
                            leftMargin: 50
                            right: dep_title_block.right
                        }

                    }

                    Row {
                        id: dep_title_block

                        anchors {
                            left: parent.left
                            leftMargin: 60
                        }

                        Image {
                            source: icon
                            fillMode: Image.PreserveAspectFit

                            anchors {
                                top: parent.top
                                topMargin: 5
                                bottom: parent.bottom
                                bottomMargin: 5
                            }

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

                        text: qsTr("时间：%1").arg(time)
                        font.pixelSize: 36

                        anchors {
                            top: dep_title_block_rect.bottom
                            topMargin: 20
                            left: dep_title_block_rect.left
                            right: parent.right
                        }

                    }

                    Text {
                        id: loc_txt

                        text: qsTr("地点：%1").arg(loc)
                        font.pixelSize: 36

                        anchors {
                            top: time_txt.bottom
                            topMargin: 10
                            left: dep_title_block_rect.left
                            right: parent.right
                        }

                    }

                    Text {
                        id: topic_txt

                        text: qsTr("主题：%1").arg(topic)
                        font.pixelSize: 36

                        anchors {
                            top: loc_txt.bottom
                            topMargin: 10
                            left: dep_title_block_rect.left
                            right: parent.right
                        }

                    }

                }

            }

        }

        Text {
            text: "本周暂无授课，敬请期待！"
            font.pixelSize: 56
            horizontalAlignment: Text.AlignHCenter
            visible: LessonModel.rowCount() === 0

            anchors {
                top: bg_image.bottom
                left: parent.left
                right: parent.right
            }

        }

    }

}
