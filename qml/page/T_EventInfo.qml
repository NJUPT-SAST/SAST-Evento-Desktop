import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    property var arr: []

    onErrorClicked: {
        loadEventoInfo(EventoHelper.id)
    }

    function loadEventoInfo(id) {
        statusMode = FluStatusViewType.Loading
        EventoInfoController.loadEventoInfo(id)
    }

    Component.onCompleted: {
        loadEventoInfo(EventoHelper.id)
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
        Layout.bottomMargin: 10
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
        font: FluTextStyle.TitleLarge
        Connections {
            target: EventoInfoController
            function onLoadEventoSuccessEvent() {
                item_title.text = EventoHelper.title
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
        id: item_location
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
        id: item_department
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
        id: item_type
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
        id: item_tag
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

    FluText {
        id: item_desc
        Layout.topMargin: 15
        Layout.fillWidth: true
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 18
        Connections {
            target: EventoInfoController
            function onLoadEventoSuccessEvent() {
                item_desc.text = EventoHelper.description
            }
        }
    }

    FluToggleButton {
        id: btn_participate
        Layout.topMargin: 10
        Layout.fillWidth: true
        text: lang.lang_participate_in
        disabled: false
        onClicked: {
            if (checked) {
                text = lang.lang_cancel
                showSuccess("参加成功")
            } else {
                text = lang.lang_participate_in
                showSuccess("取消成功")
            }
        }
    }

    Loader {
        id: loader
        sourceComponent: com_comment
        Layout.topMargin: 15
        Layout.fillWidth: true
    }

    Component {
        id: com_comment
        Column {
            width: parent.width
            spacing: 15

            FluText {
                text: lang.lang_comment
                font: FluTextStyle.Subtitle
            }

            FluText {
                text: "为本活动打个分吧，你的评价会被匿名上传哦"
                font: FluTextStyle.Caption
            }

            FluRatingControl {}

            FluMultilineTextBox {
                placeholderText: "输入你的留言（选填，Ctrl+Enter换行）"
                width: parent.width
            }

            FluButton {
                text: lang.lang_submit
                onClicked: {
                    showSuccess("提交成功")
                }
            }
        }
    }
}
