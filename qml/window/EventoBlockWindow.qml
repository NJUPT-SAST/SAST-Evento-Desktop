import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI
import SAST_Evento
import "../imports"

CustomWindow {
    id: window
    width: 290
    height: 378
    closeDestory: true
    showMinimize: false
    showMaximize: false
    fixSize: true
    launchMode: FluWindowType.SingleInstance

    property var arr: []

    Component.onCompleted: {
        loadEventoInfo()
    }

    function loadEventoInfo() {
        showLoading()
        CalendarController.loadEventoInfo(EventoHelper.id)
    }

    Connections {
        target: CalendarController
        function onLoadEventoSuccessEvent() {
            arr = []
            loader.sourceComponent = slide_com
            hideLoading()
        }
    }

    Connections {
        target: loader
        function onSourceComponentChanged() {
            if (loader.sourceComponent !== undefined) {
                carousel.model = arr
            }
            loader.sourceComponent = undefined
        }
    }

    Connections {
        target: CalendarController
        function onLoadEventoErrorEvent(message) {
            hideLoading()
            MainWindow.window.showError(message)
            window.close()
        }
    }

    Loader {
        id: loader
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

    FluScrollablePage {
        anchors.fill: parent
        Item {
            height: btn_delete.height
            width: 62
            visible: EventoEditHelper.isEdited
            FluIconButton {
                iconSource: FluentIcons.Edit
                iconSize: 15
                onClicked: {
                    EventoEditHelper.isEdited = true
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
            buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
            negativeText: "取消"
            positiveText: "确定"
            onPositiveClicked: {
                showLoading()
                CalendarController.deleteEvento(EventoHelper.id)
            }
        }

        Connections {
            target: CalendarController
            function onDeleteSuccessEvent() {
                hideLoading()
                window.close()
            }
        }

        Connections {
            target: CalendarController
            function onDeleteErrorEvent(message) {
                hideLoading()
            }
        }

        FluCarousel {
            id: carousel
            width: 300
            height: 150
            radius: [5, 5, 5, 5]
            loopTime: 4000
            indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
            indicatorMarginTop: 5

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
