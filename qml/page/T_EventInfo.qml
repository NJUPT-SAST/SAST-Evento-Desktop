import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    property var arr: []
    property int score_value: 0
    property string feedback_content

    onErrorClicked: {
        loadEventoInfo()
    }

    function loadEventoInfo() {
        statusMode = FluStatusViewType.Loading
        EventoInfoController.loadEventoInfo(EventoHelper.id)
    }

    Component.onCompleted: {
        loadEventoInfo()
    }

    Connections {
        target: EventoInfoController
        function onLoadEventoSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: EventoInfoController
        function onLoadEventoErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Repeater {
        id: rep
        model: SlideModel

        Item {
            Connections {
                target: EventoInfoController
                function onLoadEventoSuccessEvent() {
                    arr.push({
                                 "url": model.url,
                                 "title": model.title
                             })
                    if (arr.length === 3)
                        rep.arrReady()
                }
            }
        }

        signal arrReady
    }

    FluCarousel {
        id: carousel
        Layout.topMargin: 10
        Layout.fillWidth: true
        radius: [10, 10, 10, 10]
        loopTime: 4000
        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
        indicatorMarginTop: 15

        Connections {
            target: rep
            function onArrReady() {
                carousel.model = arr
            }
        }

        delegate: Component {
            Item {
                anchors.fill: parent
                Image {
                    anchors.fill: parent
                    source: model.url
                    asynchronous: true
                    fillMode: Image.PreserveAspectCrop
                }
                Rectangle {
                    height: 40
                    width: parent.width
                    anchors.bottom: parent.bottom
                    color: "#33000000"
                    FluText {
                        anchors.fill: parent
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        text: model.title
                        color: FluColors.Grey10
                        font.pixelSize: 15
                    }
                }
            }
        }
    }

    FluText {
        id: item_title
        Layout.topMargin: 10
        font: FluTextStyle.TitleLarge
        Connections {
            target: EventoInfoController
            function onLoadEventoSuccessEvent() {
                item_title.text = EventoHelper.title
            }
        }
    }

    Row {
        Layout.fillWidth: true
        spacing: 13
        ColumnLayout {
            width: parent.width / 2 + 135
            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.EmojiTabFavorites
                }
                FluText {
                    id: text_eventTime
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    Connections {
                        target: EventoInfoController
                        function onLoadEventoSuccessEvent() {
                            text_eventTime.text = "活动时间：" + EventoHelper.eventTime
                        }
                    }
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.EmojiTabFavorites
                }
                FluText {
                    id: text_registerTime
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    Connections {
                        target: EventoInfoController
                        function onLoadEventoSuccessEvent() {
                            text_registerTime.text = "报名时间：" + EventoHelper.registerTime
                        }
                    }
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.POI
                }
                FluText {
                    id: text_loc
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    Connections {
                        target: EventoInfoController
                        function onLoadEventoSuccessEvent() {
                            text_loc.text = EventoHelper.location
                        }
                    }
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.EMI
                }
                FluText {
                    id: text_dep
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    Connections {
                        target: EventoInfoController
                        function onLoadEventoSuccessEvent() {
                            text_dep.text = EventoHelper.department
                        }
                    }
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.OEM
                }
                FluText {
                    id: text_type
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    Connections {
                        target: EventoInfoController
                        function onLoadEventoSuccessEvent() {
                            text_type.text = EventoHelper.type
                        }
                    }
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 8
                FluIcon {
                    iconSource: FluentIcons.Tag
                }
                FluRectangle {
                    height: 20
                    width: 50
                    radius: [5, 5, 5, 5]
                    color: "#99ffcc"
                    FluText {
                        id: text_tag
                        wrapMode: Text.WordWrap
                        font: FluTextStyle.Caption
                        color: FluColors.Grey100
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        Connections {
                            target: EventoInfoController
                            function onLoadEventoSuccessEvent() {
                                text_tag.text = EventoHelper.tag
                            }
                        }
                    }
                }
            }
        }

        FluRectangle {
            width: 4
            height: parent.height - 20
            radius: [2, 2, 2, 2]
            color: FluTheme.primaryColor.normal
            anchors.verticalCenter: parent.verticalCenter
        }

        ColumnLayout {
            width: parent.width / 2 - 135
            anchors.verticalCenter: parent.verticalCenter
            FluToggleButton {
                id: btn_register
                implicitWidth: 250
                text: EventoHelper.isRegistrated ? "取消报名" : "报名活动"
                checked: EventoHelper.isRegistrated
                disabled: EventoHelper.isParticipated

                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.isRegistrated = !EventoHelper.isRegistrated
                    EventoInfoController.registerEvento(
                                EventoHelper.id, EventoHelper.isRegistrated)
                }
            }
            Connections {
                target: EventoInfoController
                function onRegisterSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess((EventoHelper.isRegistrated ? "报名成功" : "已取消"))
                    loadEventoInfo()
                }
            }
            Connections {
                target: EventoInfoController
                function onRegisterErrorEvent(message) {
                    showError("错误：" + message)
                    loadEventoInfo()
                }
            }

            FluToggleButton {
                id: btn_subscribe
                implicitWidth: 250
                Layout.topMargin: 20
                text: EventoHelper.isSubscribed ? "取消订阅" : "订阅活动"
                checked: EventoHelper.isSubscribed
                disabled: EventoHelper.isParticipated

                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.isSubscribed = !EventoHelper.isSubscribed
                    EventoInfoController.subscribeEvento(
                                EventoHelper.id, EventoHelper.isSubscribed)
                }
            }
            Connections {
                target: EventoInfoController
                function onSubscribeSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess((EventoHelper.isSubscribed ? "订阅成功" : "已取消"))
                    loadEventoInfo()
                }
            }
            Connections {
                target: EventoInfoController
                function onSubscribeErrorEvent(message) {
                    showError("错误：" + message)
                    loadEventoInfo()
                }
            }

            FluText {
                id: text_subs_info
                text: "订阅后小程序将在活动开始前通知您"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluButton {
                id: btn_check
                implicitWidth: 250
                text: EventoHelper.isParticipated ? "已签到" : "签到"
                disabled: EventoHelper.isParticipated
                Layout.topMargin: 15
                onClicked: {
                    dialog.open()
                }
            }
        }
    }

    FluText {
        id: item_desc
        Layout.topMargin: 15
        width: parent.width
        wrapMode: Text.WordWrap
        font.pixelSize: 18
        Connections {
            target: EventoInfoController
            function onLoadEventoSuccessEvent() {
                item_desc.text = EventoHelper.description
            }
        }
    }

    FluContentDialog {
        id: dialog
        title: ""
        message: "使用小程序扫描二维码或输入密钥"
        negativeText: "取消"

        Item {
            anchors {
                left: parent.left
                top: parent.top
                leftMargin: parent.width / 2 - 175
                topMargin: parent.height / 2 - 60
            }

            FluTextBox {
                id: textbox
                width: 350
                placeholderText: "密钥请向讲师获取哦"
            }
        }

        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        positiveText: "签到"
        onPositiveClicked: {
            if (textbox.text === "") {
                showError("输入为空")
                dialog.open()
            } else {
                statusMode = FluStatusViewType.Loading
                ScheduleController.check(EventoHelper.id, textbox.text)
            }
        }
    }

    Connections {
        target: ScheduleController
        function onCheckSuccessEvent() {
            statusMode = FluStatusViewType.Success
            showSuccess("签到成功")
            loadEventoInfo()
        }
    }

    Connections {
        target: ScheduleController
        function onCheckErrorEvent(message) {
            showError("错误：" + message)
            loadEventoInfo()
        }
    }

    Loader {
        id: loader
        sourceComponent: EventoHelper.isParticipated ? com_comment : undefined
        Layout.topMargin: 15
        Layout.fillWidth: true
    }

    Component {
        id: com_comment
        Column {
            width: parent.width
            spacing: 15

            FluText {
                text: "反馈"
                font: FluTextStyle.Subtitle
            }

            FluText {
                text: "为本次活动打个分吧，你的反馈会被匿名上传哦"
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }

            FluRatingControl {
                id: rating
                value: EventoHelper.isfeedback ? FeedbackHelper.score : score_value
            }

            FluMultilineTextBox {
                id: textbox_content
                placeholderText: "输入你的留言（选填，Ctrl+Enter换行）"
                text: EventoHelper.isfeedback ? FeedbackHelper.content : feedback_content
                width: parent.width
            }

            FluFilledButton {
                implicitWidth: 200
                text: EventoHelper.isfeedback ? "修改并提交" : "提交反馈"
                disabled: rating.value === 0
                anchors.right: parent.right
                onClicked: {
                    score_value = rating.value
                    feedback_content = textbox_content.text
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.feedbackEvento(score_value, content,
                                                EventoHelper.id)
                }
            }

            Connections {
                target: EventoInfoController
                function onFeedbackSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess("已提交")
                    loadEventoInfo()
                }
            }

            Connections {
                target: EventoInfoController
                function onFeedbackErrorEvent(message) {
                    showError("错误：" + message)
                    loadEventoInfo()
                }
            }
        }
    }
}
