import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import MyModel

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    property var arr: []
    property int eventId

    onErrorClicked: {
        loadEventoInfo(eventId)
    }

    function loadEventoInfo(id) {
        statusMode = FluStatusViewType.Loading
        controller.loadEventoInfo(id)
    }

    Component.onCompleted: {
        eventId = EventoHelper.id
        loadEventoInfo(eventId)
    }

    EventoInfoController {
        id: controller
        onLoadEventoSuccessEvent: {
            statusMode = FluStatusViewType.Success
        }
        onLoadEventoErrorEvent: message => {
                                    errorText = message
                                    statusMode = FluStatusViewType.Error
                                }
    }

    Repeater {
        id: rep
        model: SlideModel

        Item {
            Connections {
                target: controller
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
        loopTime: 3000
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
        text: EventoHelper.title
        font: FluTextStyle.TitleLarge
    }

    Row {
        spacing: 5
        Layout.topMargin: 8
        FluIcon {
            iconSource: FluentIcons.EmojiTabFavorites
        }
        FluText {
            text: "活动时间：" + EventoHelper.eventTime
            wrapMode: Text.WordWrap
            font: FluTextStyle.Caption
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Row {
        spacing: 5
        Layout.topMargin: 8
        FluIcon {
            iconSource: FluentIcons.EmojiTabFavorites
        }
        FluText {
            text: "报名时间：" + EventoHelper.registerTime
            wrapMode: Text.WordWrap
            font: FluTextStyle.Caption
            anchors.verticalCenter: parent.verticalCenter
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
            text: EventoHelper.location
            wrapMode: Text.WordWrap
            font: FluTextStyle.Caption
            anchors.verticalCenter: parent.verticalCenter
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
            text: EventoHelper.department
            wrapMode: Text.WordWrap
            font: FluTextStyle.Caption
            anchors.verticalCenter: parent.verticalCenter
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
            text: EventoHelper.type
            wrapMode: Text.WordWrap
            font: FluTextStyle.Caption
            anchors.verticalCenter: parent.verticalCenter
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
                text: EventoHelper.tag
                wrapMode: Text.WordWrap
                font: FluTextStyle.Caption
                color: FluColors.Grey100
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    FluText {
        id: item_desc
        Layout.topMargin: 15
        Layout.fillWidth: true
        text: EventoHelper.description
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 18
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

            FluTextBox {
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
