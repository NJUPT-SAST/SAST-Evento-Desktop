import "../component"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollableStatusPage {
    id: page

    property var arr: []
    property int score_value: 0
    property string feedback_content

    signal listReady()

    function loadEventoInfo() {
        arr = [];
        EventoInfoController.loadEventoInfo(EventoHelper.id);
    }

    function convert2Color(s) {
        switch (s) {
        case 1:
            return FluColors.Blue.normal;
        case 2:
            return FluColors.Green.normal;
        case 3:
            return FluColors.Orange.normal;
        case 4:
            return FluColors.Red.normal;
        case 5:
            return FluColors.Grey110;
        default:
            return null;
        }
    }

    function convert2Text(s) {
        switch (s) {
        case 1:
            return lang.lang_not_started;
        case 2:
            return lang.lang_registering;
        case 3:
            return lang.lang_undertaking;
        case 4:
            return lang.lang_cancelled;
        case 5:
            return lang.lang_over;
        default:
            return "";
        }
    }

    launchMode: FluPageType.SingleTask
    Component.onCompleted: {
        statusMode = FluStatusLayoutType.Loading;
        loadEventoInfo();
    }
    onErrorClicked: {
        statusMode = FluStatusLayoutType.Loading;
        loadEventoInfo();
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    Connections {
        function onLoadEventoSuccessEvent() {
            arr = [];
            loader_slide.sourceComponent = slide_com;
            page.listReady();
            statusMode = FluStatusLayoutType.Success;
            btn_subscribe.loading = false;
            btn_register.loading = false;
        }

        target: EventoInfoController
    }

    Connections {
        function onLoadEventoErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: EventoInfoController
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
                    });
                }
            }

        }

    }

    Connections {
        function onListReady() {
            carousel.model = arr;
            loader_slide.sourceComponent = undefined;
        }

        target: page
    }

    FluCarousel {
        id: carousel

        Layout.topMargin: 10
        Layout.fillWidth: true
        height: width * 40 / 89
        implicitHeight: height
        loopTime: 4000
        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
        indicatorMarginTop: 15

        delegate: FluClip {
            anchors.fill: parent
            radius: [10, 10, 10, 10]

            FluImage {
                anchors.fill: parent
                source: model.url
                asynchronous: true
                fillMode: Image.PreserveAspectCrop
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
            id: info_col

            width: parent.width / 2 + 70

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
                    width: text_tag.implicitWidth + 5
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
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
            width: 4
            radius: [2, 2, 2, 2]
            color: FluTheme.primaryColor
            visible: UserHelper.permission
        }

        ColumnLayout {
            width: parent.width - 30 - info_col.width
            anchors.verticalCenter: parent.verticalCenter
            visible: UserHelper.permission

            FluText {
                id: text_evento_state

                font: FluTextStyle.Subtitle
                text: convert2Text(EventoHelper.state)
                color: convert2Color(EventoHelper.state)
            }

            FluToggleButton {
                id: btn_register

                property bool loading: false

                Layout.topMargin: 15
                implicitWidth: parent.width
                checked: EventoInfoController.isRegistrated
                disabled: EventoHelper.state != 2 || loading
                onClicked: {
                    loading = true;
                    EventoInfoController.isRegistrated = !EventoInfoController.isRegistrated;
                    EventoInfoController.registerEvento(EventoHelper.id, EventoInfoController.isRegistrated);
                }

                contentItem: Row {
                    spacing: 6

                    FluText {
                        text: EventoInfoController.isRegistrated ? lang.lang_cancellation : lang.lang_register
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        color: {
                            if (btn_register.disabled)
                                return Qt.rgba(160 / 255, 160 / 255, 160 / 255, 1);
                            else
                                return FluTheme.dark ? FluColors.White : FluColors.Grey220;
                        }
                    }

                    Item {
                        width: btn_register.loading ? 16 : 0
                        height: 16
                        anchors.verticalCenter: parent.verticalCenter
                        visible: width !== 0
                        clip: true

                        FluProgressRing {
                            width: 16
                            height: 16
                            strokeWidth: 3
                            anchors.centerIn: parent
                        }

                        Behavior on width {
                            enabled: FluTheme.animationEnabled

                            NumberAnimation {
                                duration: 167
                                easing.type: Easing.OutCubic
                            }

                        }

                    }

                }

            }

            Connections {
                function onRegisterSuccessEvent() {
                    statusMode = FluStatusLayoutType.Success;
                    showSuccess((EventoInfoController.isRegistrated ? lang.lang_register_success : lang.lang_cancelled));
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

            Connections {
                function onRegisterErrorEvent(message) {
                    showError(lang.lang_error + message);
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

            FluToggleButton {
                id: btn_subscribe

                property bool loading: false

                implicitWidth: parent.width
                Layout.topMargin: 15
                checked: EventoInfoController.isSubscribed
                disabled: EventoHelper.state > 2 || loading
                onClicked: {
                    loading = true;
                    EventoInfoController.isSubscribed = !EventoInfoController.isSubscribed;
                    EventoInfoController.subscribeEvento(EventoHelper.id, EventoInfoController.isSubscribed);
                }

                contentItem: Row {
                    spacing: 6

                    FluText {
                        text: EventoInfoController.isSubscribed ? lang.lang_unsubscribe : lang.lang_subscribe
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        color: {
                            if (btn_subscribe.disabled)
                                return Qt.rgba(160 / 255, 160 / 255, 160 / 255, 1);
                            else
                                return FluTheme.dark ? FluColors.White : FluColors.Grey220;
                        }
                    }

                    Item {
                        width: btn_subscribe.loading ? 16 : 0
                        height: 16
                        anchors.verticalCenter: parent.verticalCenter
                        visible: width !== 0
                        clip: true

                        FluProgressRing {
                            width: 16
                            height: 16
                            strokeWidth: 3
                            anchors.centerIn: parent
                        }

                        Behavior on width {
                            enabled: FluTheme.animationEnabled

                            NumberAnimation {
                                duration: 167
                                easing.type: Easing.OutCubic
                            }

                        }

                    }

                }

            }

            Connections {
                function onSubscribeSuccessEvent() {
                    showSuccess((EventoInfoController.isSubscribed ? lang.lang_subscribe_success : lang.lang_cancelled));
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

            Connections {
                function onSubscribeErrorEvent(message) {
                    showError(lang.lang_error + message);
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

            FluText {
                id: text_subs_info

                text: lang.lang_subscribe_hint
                Layout.fillWidth: true
                elide: Text.ElideRight
                maximumLineCount: 2
                wrapMode: Text.WordWrap
                font: FluTextStyle.Caption
                color: FluColors.Grey110
            }

            FluButton {
                id: btn_check

                implicitWidth: parent.width
                Layout.topMargin: 9
                text: EventoInfoController.isParticipated ? lang.lang_checked_in : lang.lang_check_in
                disabled: EventoInfoController.isParticipated
                onClicked: {
                    dialog.open();
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
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        positiveText: lang.lang_check_in
        onPositiveClicked: {
            if (textbox.text === "") {
                showError(lang.lang_input_is_empty);
                dialog.open();
            } else {
                statusMode = FluStatusLayoutType.Loading;
                ScheduleController.check(EventoHelper.id, textbox.text, false);
            }
        }

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

    }

    Connections {
        function onCheckSuccessEvent(refreshAll) {
            if (!refreshAll) {
                statusMode = FluStatusLayoutType.Success;
                showSuccess(lang.lang_check_success);
                loadEventoInfo();
            }
        }

        target: ScheduleController
    }

    Connections {
        function onCheckErrorEvent(message) {
            showError(lang.lang_error + message);
            loadEventoInfo();
        }

        target: ScheduleController
    }

    Loader {
        id: loader

        Layout.topMargin: 15
        Layout.fillWidth: true
        sourceComponent: (EventoInfoController.isParticipated && EventoHelper.state === 5 && UserHelper.permission !== 1) ? com_comment : undefined
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
                    score_value = rating.value;
                    feedback_content = textbox_content.text;
                    statusMode = FluStatusLayoutType.Loading;
                    EventoInfoController.feedbackEvento(score_value, feedback_content, EventoHelper.id);
                }
            }

            Connections {
                function onFeedbackSuccessEvent() {
                    statusMode = FluStatusLayoutType.Success;
                    showSuccess(lang.lang_submit_success);
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

            Connections {
                function onFeedbackErrorEvent(message) {
                    showError(lang.lang_error + message);
                    loadEventoInfo();
                }

                target: EventoInfoController
            }

        }

    }

}
