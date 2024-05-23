import "../component"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window 2.2
import SAST_Evento

FluWindow {
    id: window

    property int windowWidth: 290
    property int windowHeight: 380

    width: 290
    height: 380
    minimumWidth: windowWidth
    minimumHeight: windowHeight
    maximumWidth: windowWidth
    maximumHeight: windowHeight
    fixSize: true
    launchMode: FluWindowType.SingleInstance

    FluScrollableStatusPage {
        id: page

        property string code: ""
        property var arr: []
        property int windowX
        property int windowY

        anchors.fill: parent
        onErrorClicked: {
            if (loader.sourceComponent === com_qrCode)
                loadQRcode();
            else
                loadEventoInfo();
        }

        Loader {
            id: page_loader

            sourceComponent: com_info
        }

        Component {
            id: com_qrCode

            Item {
                function loadQRcode() {
                    page.statusMode = FluStatusLayoutType.Loading;
                    CalendarController.loadCheckCode(EventoHelper.id);
                }

                height: window.height
                width: window.width
                Component.onCompleted: {
                    loadQRcode();
                }

                Shortcut {
                    sequence: "Ctrl+C"
                    context: Qt.WindowShortcut
                    onActivated: {
                        FluTools.clipText(code_text.text);
                        showSuccess(lang.lang_copy_success);
                    }
                }

                Shortcut {
                    sequence: "Esc"
                    context: Qt.WindowShortcut
                    onActivated: {
                        window.visibility = Window.Windowed;
                        window.x = page.windowX;
                        window.y = page.windowY;
                        minimumWidth = windowWidth;
                        minimumHeight = windowHeight;
                        maximumWidth = windowWidth;
                        maximumHeight = windowHeight;
                        page_loader.sourceComponent = com_info;
                    }
                }

                Connections {
                    function onLoadCheckCodeSuccessEvent(code) {
                        page.code = code;
                        page.statusMode = FluStatusLayoutType.Success;
                    }

                    target: CalendarController
                }

                Connections {
                    function onLoadCheckCodeErrorEvent(message) {
                        page.errorText = message;
                        page.statusMode = FluStatusLayoutType.Error;
                    }

                    target: CalendarController
                }

                FluIconButton {
                    iconSource: FluentIcons.Back
                    iconSize: 15
                    onClicked: {
                        window.visibility = Window.Windowed;
                        window.x = page.windowX;
                        window.y = page.windowY;
                        minimumWidth = windowWidth;
                        minimumHeight = windowHeight;
                        maximumWidth = windowWidth;
                        maximumHeight = windowHeight;
                        page_loader.sourceComponent = com_info;
                    }

                    anchors {
                        top: parent.top
                        topMargin: 5
                        left: parent.left
                    }

                }

                FluQRCode {
                    id: qrCode

                    text: page.code
                    size: Screen.desktopAvailableHeight - 200

                    anchors {
                        left: parent.left
                        leftMargin: Screen.desktopAvailableWidth / 2 - qrCode.size / 2
                        top: parent.top
                        topMargin: 35
                    }

                }

                FluText {
                    id: code_text

                    text: page.code
                    font.pixelSize: 90
                    horizontalAlignment: Text.AlignHCenter

                    anchors {
                        top: qrCode.bottom
                        topMargin: 15
                        left: parent.left
                        leftMargin: Screen.desktopAvailableWidth / 2 - code_text.implicitWidth / 2 - 40
                    }

                }

                FluIconButton {
                    id: btn_cpy

                    iconSource: FluentIcons.Copy
                    text: lang.lang_copy
                    iconSize: 80
                    onClicked: {
                        FluTools.clipText(code_text.text);
                        showSuccess(lang.lang_copy_success);
                    }

                    anchors {
                        top: code_text.top
                        left: code_text.right
                        leftMargin: 5
                    }

                }

            }

        }

        Component {
            id: com_info

            Item {
                id: item_all

                signal listReady()

                function loadEventoInfo() {
                    page.statusMode = FluStatusLayoutType.Loading;
                    CalendarController.loadEventoInfo(EventoHelper.id);
                }

                width: 290
                implicitHeight: 15 + col.height
                Component.onCompleted: {
                    loadEventoInfo();
                }

                Component {
                    id: slide_com

                    Repeater {
                        id: rep

                        model: SlideModel

                        Item {
                            Component.onCompleted: {
                                page.arr.push({
                                    "url": model.url
                                });
                            }
                        }

                    }

                }

                Connections {
                    function onLoadEventoSuccessEvent() {
                        page.arr = [];
                        loader.sourceComponent = slide_com;
                        item_all.listReady();
                        page.statusMode = FluStatusLayoutType.Success;
                    }

                    target: EventoInfoController
                }

                Connections {
                    function onLoadEventoErrorEvent(message) {
                        page.statusMode = FluStatusLayoutType.Error;
                        window.showError(message);
                        window.close();
                    }

                    target: EventoInfoController
                }

                Connections {
                    function onListReady() {
                        carousel.model = page.arr;
                        loader.sourceComponent = undefined;
                    }

                    target: item_all
                }

                Loader {
                    id: loader

                    sourceComponent: undefined
                }

                FluIconButton {
                    id: btn_back

                    iconSource: FluentIcons.Back
                    iconSize: 15
                    onClicked: {
                        window.close();
                    }

                    anchors {
                        left: parent.left
                    }

                }

                Item {
                    z: 999
                    height: btn_delete.height
                    width: 270
                    visible: EventoInfoController.editable

                    FluIconButton {
                        iconSource: FluentIcons.QRCode
                        iconSize: 15
                        text: lang.lang_get_qrcode
                        onClicked: {
                            page.windowX = window.x;
                            page.windowY = window.y;
                            minimumWidth = Screen.desktopAvailableWidth;
                            minimumHeight = Screen.desktopAvailableHeight;
                            maximumWidth = Screen.desktopAvailableWidth;
                            maximumHeight = Screen.desktopAvailableHeight;
                            window.visibility = Window.FullScreen;
                            page_loader.sourceComponent = com_qrCode;
                            showInfo("press \"Esc\" to exit fullscreen\npress \"Ctrl+C\" to copy code", 4000);
                        }

                        anchors {
                            right: btn_edit.left
                        }

                    }

                    FluIconButton {
                        id: btn_edit

                        iconSource: FluentIcons.Edit
                        iconSize: 15
                        text: lang.lang_edit_event
                        onClicked: {
                            EventoEditController.isEditMode = true;
                            setResult({
                                "enterPage": true
                            });
                            window.close();
                        }

                        anchors {
                            right: btn_cancel.left
                        }

                    }

                    FluIconButton {
                        id: btn_cancel

                        iconSource: FluentIcons.Cancel
                        iconSize: 15
                        text: lang.lang_cancel_event
                        onClicked: {
                            cancel_btn_dialog.open();
                            window.close();
                        }

                        anchors {
                            right: btn_delete.left
                        }

                    }

                    FluIconButton {
                        id: btn_delete

                        iconSource: FluentIcons.Delete
                        iconSize: 15
                        text: lang.lang_delete_event
                        onClicked: {
                            delete_btn_dialog.open();
                        }

                        anchors {
                            right: parent.right
                        }

                    }

                }

                FluContentDialog {
                    id: delete_btn_dialog

                    title: lang.lang_delete_event
                    message: lang.lang_confirm_delete
                    buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
                    negativeText: lang.lang_cancel
                    positiveText: lang.lang_ok
                    onPositiveClicked: {
                        page.statusMode = FluStatusLayoutType.Loading;
                        CalendarController.deleteEvento(EventoHelper.id);
                    }
                }

                FluContentDialog {
                    id: cancel_btn_dialog

                    title: lang.lang_cancel_event
                    message: lang.lang_confirm_cancel
                    buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
                    negativeText: lang.lang_cancel
                    positiveText: lang.lang_ok
                    onPositiveClicked: {
                        page.statusMode = FluStatusLayoutType.Loading;
                        CalendarController.cancelEvento(EventoHelper.id);
                    }
                }

                Connections {
                    function onDeleteSuccessEvent() {
                        page.statusMode = FluStatusLayoutType.Success;
                        window.close();
                    }

                    target: CalendarController
                }

                Connections {
                    function onDeleteErrorEvent(message) {
                        page.statusMode = FluStatusLayoutType.Success;
                    }

                    target: CalendarController
                }

                ColumnLayout {
                    id: col

                    width: 270

                    FluCarousel {
                        id: carousel

                        width: 270
                        height: 150
                        loopTime: 4000
                        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
                        indicatorMarginTop: 0
                        Layout.topMargin: 30

                        delegate: FluClip {
                            anchors.fill: parent
                            radius: [5, 5, 5, 5]

                            Image {
                                anchors.fill: parent
                                source: model.url
                                asynchronous: true
                                fillMode: Image.PreserveAspectCrop
                            }

                        }

                    }

                    FluText {
                        id: item_title

                        Layout.topMargin: 5
                        font: FluTextStyle.Title
                        text: EventoHelper.title
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }

                    Row {
                        spacing: 5
                        Layout.topMargin: 8

                        FluIcon {
                            iconSource: FluentIcons.EmojiTabFavorites
                        }

                        FluText {
                            id: text_eventTime

                            Layout.fillWidth: true
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

                            Layout.fillWidth: true
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

                            Layout.fillWidth: true
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

                            Layout.fillWidth: true
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

                            Layout.fillWidth: true
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

                                font: FluTextStyle.Caption
                                color: FluColors.Grey100
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: EventoHelper.tag
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

                }

            }

        }

    }

    appBar: FluAppBar {
        height: 0
    }

}
