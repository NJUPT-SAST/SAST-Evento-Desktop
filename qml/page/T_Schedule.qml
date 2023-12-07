import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask
    Layout.fillWidth: true

    onErrorClicked: {
        loadScheduleInfo()
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    function loadRegisteredScheduleInfo() {
        showLoading()
        ScheduleController.loadRegisteredSchedule()
    }

    function loadSubscribedScheduleInfo() {
        showLoading()
        ScheduleController.loadSubscribedSchedule()
    }

    function loadScheduleInfo(){
        if (pivot.currentIndex === 0) {
            loadRegisteredScheduleInfo() 
        }
        else if (pivot.currentIndex === 1) {
            loadSubscribedScheduleInfo()
        }
        pivot.implicitHeight = Qt.binding(()=>ScheduleController.width)
    }

    Component.onCompleted: {
        loadScheduleInfo()
    }

    Connections {
        target: ScheduleController
        function onLoadRegisteredScheduleSuccessEvent() {
            statusMode = FluStatusViewType.Success
            hideLoading()
        }
    }

    Connections {
        target: ScheduleController
        function onLoadRegisteredScheduleErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Connections {
        target: ScheduleController
        function onLoadSubscribedScheduleSuccessEvent() {
            statusMode = FluStatusViewType.Success
            hideLoading()
        }
    }

    Connections {
        target: ScheduleController
        function onLoadSubscribedScheduleErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Connections {
        target: ScheduleController
        function onCheckSuccessEvent() {
            statusMode = FluStatusViewType.Success
            showSuccess(lang.lang_check_success)
            loadScheduleInfo()
        }
    }

    Connections {
        target: ScheduleController
        function onCheckErrorEvent(message) {
            showError(lang.lang_error + message)
            loadScheduleInfo()
        }
    }

    FluPivot {
        id: pivot
        currentIndex: 0

        FluPivotItem {
            id: pivot1
            title: lang.lang_registered_evento
            contentItem: ListView {
                id: registered_events
                width: parent.width
                implicitHeight: contentHeight
                interactive: false
                spacing: 5
                model: ScheduledEventoModel
                delegate: com_schedule
            }
        }
        FluPivotItem {
            id: pivot2
            title: lang.lang_subscribed_evento
            contentItem: ListView {
                id: subscribed_events
                width: parent.width
                implicitHeight: contentHeight
                interactive: false
                spacing: 5
                model: ScheduledEventoModel
                delegate: com_schedule
            }
        }
        onCurrentIndexChanged: {
            loadScheduleInfo()
        }
    }

    Component {
        id: com_schedule
        Item {
            Layout.fillWidth: true
            height: 85 + loader.height

            Loader {
                id: loader
                height: model.hasSameDate ? 0 : 20
                anchors {
                    left: parent.left
                    leftMargin: 10
                }
                sourceComponent: model.hasSameDate ? undefined : com_date
            }

            Component {
                id: com_date
                FluText {
                    text: model.date
                    font.pixelSize: 18
                }
            }

            FluArea {
                id: area_content
                width: page.width - 105
                height: 80
                anchors {
                    top: loader.bottom
                    topMargin: 5
                }

                FluRectangle {
                    id: item_division
                    width: 6
                    height: 60
                    radius: [3, 3, 3, 3]
                    color: FluTheme.primaryColor.normal
                    anchors {
                        left: parent.left
                        leftMargin: 5
                        verticalCenter: parent.verticalCenter
                    }
                }

                Column {
                    id: item_time
                    spacing: 5
                    anchors {
                        left: item_division.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluText {
                        text: model.startTime
                        font.pixelSize: 18
                    }
                    FluText {
                        text: model.endTime
                        font.pixelSize: 18
                        color: "#708090"
                    }
                }

                FluRectangle {
                    id: item_dot
                    anchors {
                        left: item_time.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    width: 6
                    height: 6
                    radius: [3, 3, 3, 3]
                    color: FluColors.Orange.normal
                }

                Column {
                    spacing: 5
                    width: parent.width
                    anchors {
                        left: item_dot.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluText {
                        text: model.title
                        font: FluTextStyle.Title
                        elide: Text.ElideRight
                        maximumLineCount: 1
                        width: page.width - 330
                        anchors {
                            left: parent.left
                            leftMargin: 12
                        }
                    }
                    FluText {
                        text: model.location
                        font: FluTextStyle.Caption
                        color: FluColors.Grey110
                        elide: Text.ElideRight
                        maximumLineCount: 1
                        width: page.width - 220 - text_department.implicitWidth
                        anchors {
                            left: parent.left
                            leftMargin: 12
                        }
                    }
                }

                FluText {
                    id: event_state
                    anchors {
                        right: parent.right
                        top: parent.top
                        topMargin: 10
                        rightMargin: 10
                    }
                    text: lang.lang_not_started
                    color: FluColors.Blue.normal
                    font.pixelSize: 20
                }

                FluText {
                    id: text_department
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                        rightMargin: 10
                        bottomMargin: 10
                    }
                    text: model.department
                    font: FluTextStyle.Caption
                    color: FluColors.Grey110
                }

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

                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        EventoHelper.id = model.id
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_EventInfo.qml")
                    }
                }
            }

            Component.onCompleted: {
                var modelState = model.state
                var isChecked = model.isChecked
                var isFeedback = model.isFeedback
                if (modelState === 1 || modelState === 2) {
                    if (isChecked)
                        state = 'BeforeAndIsChecked'
                    else
                        state = 'BeforeAndNoChecked'
                } else if (modelState === 3) {
                    if (isChecked)
                        state = 'UndertakingAndIsChecked'
                    else
                        state = 'UndertakingAndNoChecked'
                } else if (modelState === 4)
                    state = 'Cancelled'
                else if (isFeedback)
                    state = 'OverAndIsFeedback'
                else
                    state = 'OverAndNoFeedback'
            }

            FluFilledButton {
                id: btn
                anchors {
                    top: area_content.top
                    left: area_content.right
                    leftMargin: 5
                }
                height: 80
                width: 75
                font.pixelSize: 14
            }

            states: [
                State {
                    name: 'BeforeAndNoChecked'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_not_started
                        color: FluColors.Blue.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_check_in
                        disabled: false
                        onClicked: {
                            dialog.open()
                        }
                    }
                },
                State {
                    name: 'BeforeAndIsChecked'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_not_started
                        color: FluColors.Blue.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_checked_in
                        disabled: true
                    }
                },
                State {
                    name: 'UndertakingAndNoChecked'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_undertaking
                        color: FluColors.Orange.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_check_in
                        disabled: false
                        onClicked: {
                            dialog.open()
                        }
                    }
                },
                State {
                    name: 'UndertakingAndIsChecked'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_undertaking
                        color: FluColors.Orange.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_checked_in
                        disabled: true
                    }
                },
                State {
                    name: 'Cancelled'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_cancelled
                        color: FluColors.Red.normal
                    }
                    PropertyChanges {
                        target: btn
                        text: ""
                        disabled: true
                    }
                },
                State {
                    name: 'OverAndNoFeedback'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_over
                        color: FluColors.Grey110
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_feedback
                        disabled: false
                        onClicked: {
                            EventoHelper.id = model.id
                            MainWindow.window.pushPage(
                                        "qrc:/qml/page/T_EventInfo.qml")
                        }
                    }
                },
                State {
                    name: 'OverAndIsFeedback'
                    PropertyChanges {
                        target: event_state
                        text: lang.lang_over
                        color: FluColors.Grey110
                    }
                    PropertyChanges {
                        target: btn
                        text: lang.lang_modify_feedback
                        disabled: false
                        onClicked: {
                            EventoHelper.id = model.id
                            MainWindow.window.pushPage(
                                        "qrc:/qml/page/T_EventInfo.qml")
                        }
                    }
                }
            ]

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

                buttonFlags: FluContentDialogType.NegativeButton
                             | FluContentDialogType.PositiveButton
                positiveText: lang.lang_check_in
                onPositiveClicked: {
                    if (textbox.text === "") {
                        showError(lang.lang_input_is_empty)
                        dialog.open()
                    } else {
                        statusMode = FluStatusViewType.Loading
                        ScheduleController.check(model.id, textbox.text)
                    }
                }
            }
        }
    }
}
