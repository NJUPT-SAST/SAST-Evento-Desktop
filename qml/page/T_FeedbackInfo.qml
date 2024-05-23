import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollablePage {
    function loadFeedbackInfo() {
        statusMode = FluStatusViewType.Loading;
        FeedbackStatisticsController.loadFeedbackInfo(EventoHelper.id);
    }

    launchMode: FluPageType.SingleTask
    onErrorClicked: {
        loadFeedbackInfo();
    }
    Component.onCompleted: {
        loadFeedbackInfo();
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Connections {
        function onLoadFeedbackSuccessEvent() {
            statusMode = FluStatusViewType.Success;
        }

        target: FeedbackStatisticsController
    }

    Connections {
        function onLoadFeedbackErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusViewType.Error;
        }

        target: FeedbackStatisticsController
    }

    FluArea {
        Layout.fillWidth: true
        height: 90

        FluText {
            id: text_title

            text: FeedbackStatisticsHelper.title
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
                text: FeedbackStatisticsHelper.registerNum
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
                text: FeedbackStatisticsHelper.checkedNum
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
                text: FeedbackStatisticsHelper.aveScore
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
        model: FeedbackModel
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
                            if (item_mouse.containsMouse)
                                return Qt.rgba(1, 1, 1, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        } else {
                            if (item_mouse.containsMouse)
                                return Qt.rgba(0, 0, 0, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        }
                    }
                }

                FluText {
                    id: item_score

                    text: "评分：" + model.score
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

                    text: model.content
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Body

                    anchors {
                        left: item_score.left
                        right: parent.right
                        rightMargin: 20
                        top: item_score.bottom
                        topMargin: 5
                    }

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
