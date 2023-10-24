import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask
    property var arr: []
    property int score_value: 0
    property string feedback_content

    function loadEventoInfo() {
        statusMode = FluStatusViewType.Loading
        arr = []
        EventoInfoController.loadEventoInfo(EventoHelper.id)
    }

    Component.onCompleted: {
        loadEventoInfo()
    }

    onErrorClicked: {
        loadEventoInfo()
    }

    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Connections {
        target: EventoInfoController
        function onLoadEventoSuccessEvent() {
            arr = []
            loader_slide.sourceComponent = slide_com
            page.listReady()
            statusMode = FluStatusViewType.Success
        }
    }

    signal listReady

    Connections {
        target: EventoInfoController
        function onLoadEventoErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Loader {
        id: loader_slide
        sourceComponent: undefined
    }

    Component {
        id: slide_com
        Repeater {
            id: rep
            model: SlideModel
            Item {
                Component.onCompleted: {
                    arr.push({
                                 "url": model.url
                             })
                }
            }
        }
    }

    Connections {
        target: page
        function onListReady() {
            carousel.model = arr
            loader_slide.sourceComponent = undefined
        }
    }

    FluCarousel {
        id: carousel
        Layout.topMargin: 10
        Layout.fillWidth: true
        height: width * 40 / 89
        implicitHeight: height
        radius: [10, 10, 10, 10]
        loopTime: 4000
        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
        indicatorMarginTop: 15

        delegate: Component {
            Item {
                anchors.fill: parent
                FluImage {
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
        font: FluTextStyle.Title
        text: EventoHelper.title
        wrapMode: Text.WordWrap
        Layout.fillWidth: true
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
                    shadow: false
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
            visible: UserHelper.permission !== 1
            width: 4
            height: parent.height
            radius: [2, 2, 2, 2]
            color: FluTheme.primaryColor.normal
            anchors.verticalCenter: parent.verticalCenter
        }

        ColumnLayout {
            visible: UserHelper.permission !== 1
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
                text: EventoInfoController.isRegistrated ? lang.lang_cancellation : lang.lang_register
                checked: EventoInfoController.isRegistrated
                disabled: EventoHelper.state !== 2
                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoInfoController.isRegistrated = !EventoInfoController.isRegistrated
                    EventoInfoController.registerEvento(
                                EventoHelper.id,
                                EventoInfoController.isRegistrated)
                }
            }
            Connections {
                target: EventoInfoController
                function onRegisterSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess((EventoInfoController.isRegistrated ? lang.lang_register_success : lang.lang_cancelled))
                    loadEventoInfo()
                }
            }
            Connections {
                target: EventoInfoController
                function onRegisterErrorEvent(message) {
                    showError(lang.lang_error + message)
                    loadEventoInfo()
                }
            }

            FluToggleButton {
                id: btn_subscribe
                implicitWidth: 250
                Layout.topMargin: 15
                text: EventoInfoController.isSubscribed ? lang.lang_subscribe : lang.lang_subscribe
                checked: EventoInfoController.isSubscribed
                disabled: EventoHelper.state !== 2
                onClicked: {
                    statusMode = FluStatusViewType.Loading
                    EventoInfoController.isSubscribed = !EventoInfoController.isSubscribed
                    EventoInfoController.subscribeEvento(
                                EventoHelper.id,
                                EventoInfoController.isSubscribed)
                }
            }
            Connections {
                target: EventoInfoController
                function onSubscribeSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess((EventoInfoController.isSubscribed ? lang.lang_subscribe_success : lang.lang_cancelled))
                    loadEventoInfo()
                }
            }
            Connections {
                target: EventoInfoController
                function onSubscribeErrorEvent(message) {
                    showError(lang.lang_error + message)
                    loadEventoInfo()
                }
            }

            FluText {
                id: text_subs_info
                text: lang.lang_subscribe_hint
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }
            FluButton {
                id: btn_check
                implicitWidth: 250
                Layout.topMargin: 9
                text: EventoInfoController.isParticipated ? lang.lang_checked_in : lang.lang_check_in
                disabled: EventoInfoController.isParticipated
                onClicked: {
                    dialog.open()
                }
            }
        }
    }

    FluText {
        id: item_desc
        Layout.topMargin: 15
        Layout.fillWidth: true
        wrapMode: Text.WordWrap
        font.pixelSize: 18
        text: EventoHelper.description
    }

    FluContentDialog {
        id: dialog
        title: ""
        message: lang.lang_check_message
        negativeText: lang.lang_cancel

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
                placeholderText: lang.lang_check_hint
            }
        }

        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        positiveText: lang.lang_check_in
        onPositiveClicked: {
            if (textbox.text === "") {
                showError(lang.lang_input_is_empty)
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
            showSuccess(lang.lang_check_success)
            loadEventoInfo()
        }
    }

    Connections {
        target: ScheduleController
        function onCheckErrorEvent(message) {
            showError(lang.lang_error + message)
            loadEventoInfo()
        }
    }

    Loader {
        id: loader
        Layout.topMargin: 15
        Layout.fillWidth: true
        sourceComponent: (EventoInfoController.isParticipated
                          && EventoHelper.state === 5
                          && UserHelper.permisson !== 1) ? com_comment : undefined
    }

    Component {
        id: com_comment
        Column {
            width: parent.width
            spacing: 15

            FluText {
                text: lang.lang_feedback
                font: FluTextStyle.Subtitle
            }

            FluText {
                text: lang.lang_feedback_text
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }

            FluRatingControl {
                id: rating
                value: FeedbackHelper.submitted ? FeedbackHelper.score : score_value
            }

            FluMultilineTextBox {
                id: textbox_content
                placeholderText: lang.lang_feedback_hint
                width: parent.width
                text: FeedbackHelper.submitted ? FeedbackHelper.content : feedback_content
            }

            FluFilledButton {
                id: btn_submit
                implicitWidth: 200
                disabled: rating.value === 0
                anchors.right: parent.right
                text: FeedbackHelper.submitted ? lang.lang_modify_and_submit : lang.lang_submit
                onClicked: {
                    score_value = rating.value
                    feedback_content = textbox_content.text
                    statusMode = FluStatusViewType.Loading
                    EventoInfoController.feedbackEvento(score_value, content,
                                                        EventoHelper.id)
                }
            }

            Connections {
                target: EventoInfoController
                function onFeedbackSuccessEvent() {
                    statusMode = FluStatusViewType.Success
                    showSuccess(lang.lang_submit_succcess)
                    loadEventoInfo()
                }
            }

            Connections {
                target: EventoInfoController
                function onFeedbackErrorEvent(message) {
                    showError(lang.lang_error + message)
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
            return lang.lang_not_started
        case 2:
            return lang.lang_registering
        case 3:
            return lang.lang_undertaking
        case 4:
            return lang.lang_cancelled
        case 5:
            return lang.lang_over
        default:
            return ""
        }
    }
}
