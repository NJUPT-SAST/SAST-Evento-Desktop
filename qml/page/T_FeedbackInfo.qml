import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    FluArea {
        Layout.fillWidth: true
        height: 90

        FluText {
            id: text_title
            text: "活动标题"
            font: FluTextStyle.Title
            anchors {
                top: parent.top
                topMargin: 5
                left: parent.left
                leftMargin: 10
            }
        }

        RowLayout {
            id: register_num
            spacing: 10
            anchors {
                top: parent.top
                topMargin: 10
                left: text_title.right
                leftMargin: 20
            }

            FluText {
                text: "报名人数："
                font: FluTextStyle.BodyStrong
            }
            FluText {
                text: "15"
            }
        }
        RowLayout {
            id: check_num
            spacing: 10
            anchors {
                top: register_num.bottom
                topMargin: 10
                left: register_num.left
            }
            FluText {
                text: "签到人数："
                font: FluTextStyle.BodyStrong
            }
            FluText {
                text: "14"
            }
        }
        RowLayout {
            spacing: 25
            Layout.topMargin: 8
            anchors {
                top: check_num.bottom
                topMargin: 10
                left: register_num.left
            }
            FluText {
                text: "平均分："
                font: FluTextStyle.BodyStrong
            }
            FluText {
                text: "4.8"
            }
        }
    }

    FluText {
        text: "全部反馈"
        font: FluTextStyle.Subtitle
        Layout.topMargin: 10
    }

    FluText {
        text: "已隐藏无内容的反馈"
        font: FluTextStyle.Caption
        color: FluColors.Grey110
        Layout.topMargin: 3
    }

    ListView {
        id: list_view
        topMargin: 5
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        delegate: com_item
        //model: EventoBriefModel
        model: [{
                "score": 4,
                "content": "abcdeee"
            }, {
                "score": 5,
                "content": "abcdeee"
            }, {
                "score": 4,
                "content": "反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容"
            }, {
                "score": 4,
                "content": "反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容"
            }, {
                "score": 4,
                "content": "反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容"
            }, {
                "score": 4,
                "content": "反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容"
            }, {
                "score": 4,
                "content": "反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容反馈内容"
            }]
    }

    Component {
        id: com_item
        Item {
            width: parent.width
            height: 50 + item_content.lineCount * 16
            FluArea {
                radius: 8
                width: parent.width
                height: 42 + item_content.lineCount * 16
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

                FluText {
                    id: item_score
                    text: "评分：" + modelData.score
                    font: FluTextStyle.Subtitle
                    anchors {
                        left: parent.left
                        leftMargin: 12
                        top: parent.top
                        topMargin: 5
                    }
                }

                FluText {
                    id: item_content
                    anchors {
                        left: item_score.left
                        right: parent.right
                        rightMargin: 20
                        top: item_score.bottom
                        topMargin: 5
                    }
                    text: modelData.content
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Body
                }

                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }
    }
}
