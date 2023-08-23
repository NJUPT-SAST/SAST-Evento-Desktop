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
                                 "url": model.url
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
            }
        }
    }

    FluText {
        id: item_title
        Layout.topMargin: 10
        font: FluTextStyle.TitleLarge
        text: EventoHelper.title
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
                    text: "活动时间：" + EventoHelper.eventTime
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
                    text: "报名时间：" + EventoHelper.registerTime
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
                    text: EventoHelper.location
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
                    text: EventoHelper.department
                }
            }

            Row {
                spacing: 5
                Layout.topMargin: 6
                FluIcon {
                    iconSource: FluentIcons.OEM
                }
                FluText {
                    id: text_type
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    anchors.verticalCenter: parent.verticalCenter
                    text: EventoHelper.type
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
                        text: EventoHelper.tag
                    }
                }
            }
        }

        FluRectangle {
            width: 4
            height: parent.height
            radius: [2, 2, 2, 2]
            color: FluTheme.primaryColor.normal
            anchors.verticalCenter: parent.verticalCenter
        }

        ColumnLayout {
            width: parent.width / 2 - 135
            anchors.verticalCenter: parent.verticalCenter
            FluText {
                id: text_evento_state
                font: FluTextStyle.Subtitle
                text: convert2Text(EventoHelper.state)
                color: convert2Color(EventoHelper.state)
            }

            FluToggleButton {
                id: btn_register
                Layout.topMargin: 15
                implicitWidth: 250
                text: EventoHelper.isRegistrated ? "取消报名" : "报名活动"
                checked: EventoHelper.isRegistrated
                disabled: EventoHelper.state !== 2
                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.isRegistrated = !EventoHelper.isRegistrated
                    EventoInfoController.registerEvento(
                                EventoHelper.id, EventoHelper.isRegistrated)
                }

                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        btn_register.text = EventoHelper.isRegistrated ? "取消报名" : "报名活动"
                        btn_register.checked = EventoHelper.isRegistrated
                        btn_register.disabled = EventoHelper.state !== 2
                    }
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
                Layout.topMargin: 15
                text: EventoHelper.isSubscribed ? "取消订阅" : "订阅活动"
                checked: EventoHelper.isSubscribed
                disabled: EventoHelper.state !== 2
                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.isSubscribed = !EventoHelper.isSubscribed
                    EventoInfoController.subscribeEvento(
                                EventoHelper.id, EventoHelper.isSubscribed)
                }

                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        btn_subscribe.text = EventoHelper.isSubscribed ? "取消订阅" : "订阅活动"
                        btn_subscribe.checked = EventoHelper.isSubscribed
                        btn_subscribe.disabled = EventoHelper.state !== 2
                    }
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
                Layout.topMargin: 9
                text: EventoHelper.isParticipated ? "已签到" : "签到"
                disabled: EventoHelper.isParticipated
                onClicked: {
                    dialog.open()
                }

                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        btn_check.text = EventoHelper.isParticipated ? "已签到" : "签到"
                        btn_check.disabled = EventoHelper.isParticipated
                    }
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
        text: EventoHelper.description
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
        Layout.topMargin: 15
        Layout.fillWidth: true
        sourceComponent: (EventoHelper.isParticipated
                          && EventoHelper.state === 5) ? com_comment : undefined
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
                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        rating.value
                                = FeedbackHelper.isFeedback ? FeedbackHelper.score : score_value
                    }
                }
            }

            FluMultilineTextBox {
                id: textbox_content
                placeholderText: "输入你的留言（选填，Ctrl+Enter换行）"
                width: parent.width
                text: FeedbackHelper.isFeedback ? FeedbackHelper.content : feedback_content
            }

            FluFilledButton {
                id: btn_submit
                implicitWidth: 200
                disabled: rating.value === 0
                anchors.right: parent.right
                text: FeedbackHelper.isFeedback ? "修改并提交" : "提交反馈"
                onClicked: {
                    score_value = rating.value
                    feedback_content = textbox_content.text
                    statusMode = FluStatusViewType.Loading
                    EventoHelper.feedbackEvento(score_value, content,
                                                EventoHelper.id)
                }
                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        btn_submit.text = FeedbackHelper.isFeedback ? "修改并提交" : "提交反馈"
                    }
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

    function convert2Color(s) {
        switch (s) {
        case 1:
            return FluColors.Blue.normal
        case 2:
            return FluColors.Green.normal
        case 3:
            return FluColors.Orange.normal
        case 4:
            return FluColors.Red.normal
        case 5:
            return FluColors.Grey110
        default:
            return null
        }
    }

    function convert2Text(s) {
        switch (s) {
        case 1:
            return "未开始"
        case 2:
            return "报名中"
        case 3:
            return "进行中"
        case 4:
            return "已取消"
        case 5:
            return "已结束"
        default:
            return ""
        }
    }
}
