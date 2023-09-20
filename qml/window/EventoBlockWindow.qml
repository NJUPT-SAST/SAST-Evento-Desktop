import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI
import SAST_Evento
import "../imports"

CustomWindow {
    id: window
    width: 290
    height: 380
    closeDestory: true
    showMinimize: false
    showMaximize: false
    fixSize: true
    launchMode: FluWindowType.SingleInstance

    FluScrollablePage {
        id: page
        anchors.fill: parent
        property string code: ""
        property var arr: []

        onErrorClicked: {
            if (loader.sourceComponent === com_qrCode)
                loadQRcode()
            else
                loadEventoInfo()
        }

        Loader {
            id: page_loader
            width: window.width
            height: window.height
            sourceComponent: com_info
        }

        Component {
            id: com_qrCode
            Item {
                anchors.fill: parent
                implicitHeight: 490

                function loadQRcode() {
                    page.statusMode = FluStatusViewType.Loading
                    CalendarController.loadCheckCode(EventoHelper.id)
                }

                Component.onCompleted: {
                    loadQRcode()
                }

                Connections {
                    target: CalendarController
                    function onLoadCheckCodeSuccessEvent(code) {
                        page.code = code
                        page.statusMode = FluStatusViewType.Success
                    }
                }

                Connections {
                    target: CalendarController
                    function onLoadCheckCodeErrorEvent(message) {
                        page.errorText = message
                        page.statusMode = FluStatusViewType.Error
                    }
                }

                FluIconButton {
                    iconSource: FluentIcons.Back
                    iconSize: 15
                    anchors {
                        top: parent.top
                        topMargin: 5
                        left: parent.left
                    }
                    onClicked: {
                        var widthAnimation = Qt.createQmlObject(
                                    'import QtQuick 2.0; PropertyAnimation {target: window; property: "width"; to: 290; easing.type: Easing.InOutQuad}',
                                    window)
                        var heightAnimation = Qt.createQmlObject(
                                    'import QtQuick 2.0; PropertyAnimation {target: window; property: "height"; to: 380; easing.type: Easing.InOutQuad}',
                                    window)
                        widthAnimation.runningChanged.connect(function () {
                            if (!widthAnimation.running)
                                page_loader.sourceComponent = com_info
                        })
                        heightAnimation.runningChanged.connect(function () {
                            if (!heightAnimation.running)
                                page_loader.sourceComponent = com_info
                        })
                        widthAnimation.start()
                        heightAnimation.start()
                    }
                }

                FluQRCode {
                    id: qrCode
                    text: page.code
                    size: 400
                    anchors {
                        left: parent.left
                        top: parent.top
                        topMargin: 35
                    }
                }

                RowLayout {
                    anchors {
                        top: qrCode.bottom
                        topMargin: 15
                        left: parent.left
                        leftMargin: 130
                    }
                    spacing: 5
                    FluCopyableText {
                        id: code_text
                        text: "13EDX4" //page.code
                        font: FluTextStyle.Title
                    }
                    FluIconButton {
                        iconSource: FluentIcons.Copy
                        onClicked: {
                            FluTools.clipText(code_text.text)
                            showSuccess("复制成功")
                        }
                    }
                }
            }
        }

        Component {
            id: com_info

            Item {
                width: parent.width
                implicitHeight: 15 + col.height

                function loadEventoInfo() {
                    page.statusMode = FluStatusViewType.Loading
                    CalendarController.loadEventoInfo(EventoHelper.id)
                }

                Component.onCompleted: {
                    loadEventoInfo()
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
                                              })
                            }
                        }
                    }
                }

                Connections {
                    target: EventoInfoController
                    function onLoadEventoSuccessEvent() {
                        page.arr = []
                        loader.sourceComponent = slide_com
                        page.statusMode = FluStatusViewType.Success
                    }
                }

                Connections {
                    target: EventoInfoController
                    function onLoadEventoErrorEvent(message) {
                        page.statusMode = FluStatusViewType.Success
                        MainWindow.window.showError(message)
                        window.close()
                    }
                }

                Connections {
                    target: loader
                    function onSourceComponentChanged() {
                        if (loader.sourceComponent !== undefined) {
                            carousel.model = page.arr
                        }
                        loader.sourceComponent = undefined
                    }
                }

                Loader {
                    id: loader
                    sourceComponent: undefined
                }

                Item {
                    z: 999
                    height: btn_delete.height
                    width: 270
                    visible: EventoInfoController.editable

                    FluIconButton {
                        iconSource: FluentIcons.QRCode
                        iconSize: 15
                        onClicked: {
                            var widthAnimation = Qt.createQmlObject(
                                        'import QtQuick 2.0; PropertyAnimation {target: window; property: "width"; to: 420; easing.type: Easing.InOutQuad}',
                                        window)
                            var heightAnimation = Qt.createQmlObject(
                                        'import QtQuick 2.0; PropertyAnimation {target: window; property: "height"; to: 540; easing.type: Easing.InOutQuad}',
                                        window)
                            widthAnimation.runningChanged.connect(function () {
                                if (!widthAnimation.running)
                                    page_loader.sourceComponent = com_qrCode
                            })
                            heightAnimation.runningChanged.connect(function () {
                                if (!heightAnimation.running)
                                    page_loader.sourceComponent = com_qrCode
                            })
                            widthAnimation.start()
                            heightAnimation.start()
                        }
                        anchors {
                            right: btn_edit.left
                        }
                    }

                    FluIconButton {
                        id: btn_edit
                        iconSource: FluentIcons.Edit
                        iconSize: 15
                        onClicked: {
                            EventoEditController.isEditMode = true
                            onResult({
                                         "enterPage": true
                                     })
                            window.close()
                        }
                        anchors {
                            right: btn_delete.left
                        }
                    }
                    FluIconButton {
                        id: btn_delete
                        iconSource: FluentIcons.Delete
                        iconSize: 15
                        onClicked: {
                            delete_btn_dialog.open()
                        }
                        anchors {
                            right: parent.right
                        }
                    }
                }

                FluContentDialog {
                    id: delete_btn_dialog
                    title: "删除活动"
                    message: "是否确定删除活动？"
                    buttonFlags: FluContentDialogType.NegativeButton
                                 | FluContentDialogType.PositiveButton
                    negativeText: "取消"
                    positiveText: "确定"
                    onPositiveClicked: {
                        page.statusMode = FluStatusViewType.Loading
                        CalendarController.deleteEvento(EventoHelper.id)
                    }
                }

                Connections {
                    target: CalendarController
                    function onDeleteSuccessEvent() {
                        page.statusMode = FluStatusViewType.Success
                        window.close()
                    }
                }

                Connections {
                    target: CalendarController
                    function onDeleteErrorEvent(message) {
                        page.statusMode = FluStatusViewType.Success
                    }
                }

                ColumnLayout {
                    id: col
                    width: parent.width

                    FluCarousel {
                        id: carousel
                        width: 300
                        height: 150
                        radius: [5, 5, 5, 5]
                        loopTime: 4000
                        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
                        indicatorMarginTop: 5
                        Layout.topMargin: 15

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
                        Layout.topMargin: 5
                        font: FluTextStyle.TitleLarge
                        text: EventoHelper.title
                    }

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

                    FluText {
                        id: item_desc
                        Layout.topMargin: 15
                        width: parent.width
                        wrapMode: Text.WordWrap
                        font.pixelSize: 18
                        text: EventoHelper.description
                    }
                }
            }
        }
    }
}
