import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_feedback
    property int page: 1

    onErrorClicked: {
        loadFeedbackInfo(page)
    }

    function loadFeedbackInfo() {
        statusMode = FluStatusViewType.Loading
        pagination.itemCount = FeedbackStatisticsController.loadSummaryInfo(
                    page)
    }

    Component.onCompleted: {
        page = 1
        loadFeedbackInfo(page)
    }

    Connections {
        target: FeedbackStatisticsController
        function onLoadSummarySuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: FeedbackStatisticsController
        function onLoadSummaryErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    ListView {
        id: list_view
        topMargin: 10
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        delegate: com_item
        model: FeedbackSummaryModel
    }

    FluPagination {
        id: pagination
        Layout.topMargin: 10
        Layout.alignment: Qt.AlignHCenter
        pageCurrent: page
        onRequestPage: (page, size) => {
                           loadFeedbackInfo(page)
                       }
    }

    Component {
        id: com_item
        Item {
            Layout.topMargin: 10
            width: parent.width
            height: 70
            FluArea {
                radius: 8
                width: parent.width
                height: 60
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
                    id: item_title
                    text: model.title
                    font: FluTextStyle.Subtitle
                    anchors {
                        left: parent.left
                        leftMargin: 12
                        top: parent.top
                        topMargin: 5
                    }
                }

                FluText {
                    id: item_num
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_title.bottom
                        topMargin: 5
                    }
                    text: "反馈数量：" + model.feedbackNum
                    color: FluColors.Grey120
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                }

                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_FeedbackInfo.qml")
                    }
                }
            }
        }
    }
}
