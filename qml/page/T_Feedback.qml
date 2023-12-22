import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: control
    launchMode: FluPageType.SingleTask
    title: lang.lang_feedback
    property int page: 1

    onErrorClicked: {
        loadFeedbackInfo(page)
    }

    function loadFeedbackInfo(new_page) {
        statusMode = FluStatusViewType.Loading
        page = new_page
        FeedbackStatisticsController.loadSummaryInfo(page)
    }

    Component.onCompleted: {
        loadFeedbackInfo(page)
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Connections {
        target: FeedbackStatisticsController
        function onLoadSummarySuccessEvent(sum) {
            pagination.itemCount = sum
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
        width: parent.width
        implicitHeight: contentHeight
        interactive: false
        spacing: 10
        model: FeedbackNumModel

        delegate: FluArea {
            height: 60
            width: list_view.width

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
                anchors {
                    top: parent.top
                    topMargin: 5
                    left: parent.left
                    leftMargin: 12
                }
                text: title
                font: FluTextStyle.Subtitle
                elide: Text.ElideRight
            }

            FluText {
                id: item_num
                anchors {
                    top: item_title.bottom
                    topMargin: 5
                    left: item_title.left
                }
                text: "反馈数量：" + feedbackCount
                color: FluColors.Grey120
                font: FluTextStyle.Caption
            }

            MouseArea {
                id: item_mouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    EventoHelper.id = eventId
                    MainWindow.window.pushPage(
                                "qrc:/qml/page/T_FeedbackInfo.qml")
                }
            }
        }
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
}
