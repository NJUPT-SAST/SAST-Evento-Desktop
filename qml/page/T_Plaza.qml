import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: page
    launchMode: FluPageType.SingleTask
    property var arr: []

    onErrorClicked: {
        loadPlazaInfo()
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading

    function loadPlazaInfo() {
        statusMode = FluStatusViewType.Loading
        PlazaController.loadPlazaInfo()
    }

    function loadHomeSlide() {
        PlazaController.loadHomeSlide()
    }

    Component.onCompleted: {
        loadPlazaInfo()
        loadHomeSlide()
    }

    Connections {
        target: PlazaController
        function onLoadPlazaSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: PlazaController
        function onLoadPlazaErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Loader {
        id: loader
        sourceComponent: undefined
    }
    Connections {
        target: PlazaController
        function onLoadHomeSlideSuccessEvent() {
            arr = []
            loader.sourceComponent = rep_com
            page.listReady()
        }
    }

    signal listReady

    Component {
        id: rep_com
        Repeater {
            id: rep
            model: SlideModel
            Item {
                Component.onCompleted: {
                    arr.push({
                                 "url": model.url,
                                 "link": model.link,
                                 "title": model.title
                             })
                }
            }
        }
    }

    FluCarousel {
        id: carousel
        Layout.topMargin: 10
        Layout.fillWidth: true
        height: width * 0.36
        implicitHeight: height
        radius: [10, 10, 10, 10]
        loopTime: 4000
        indicatorGravity: Qt.AlignHCenter | Qt.AlignTop
        indicatorMarginTop: 10
        Connections {
            target: page
            function onListReady() {
                carousel.model = arr
                loader.sourceComponent = undefined
            }
        }

        delegate: Component {
            Item {
                width: carousel.width
                height: carousel.height
                FluImage {
                    anchors.fill: parent
                    source: model.url
                    asynchronous: true
                    cache: true
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
                MouseArea {
                    anchors.fill: parent
                    anchors.topMargin: 30
                    onClicked: {
                        PlazaController.openUrl(model.link)
                    }
                }
            }
        }
    }

    FluText {
        text: lang.lang_undertaking_evento
        font: FluTextStyle.Title
        Layout.leftMargin: 20
        Layout.topMargin: 20
    }

    GridView {
        topMargin: 10
        Layout.fillWidth: true
        implicitHeight: contentHeight
        cellHeight: 150
        cellWidth: 292
        interactive: false
        delegate: com_item
        model: UndertakingEventoModel
    }

    FluText {
        text: lang.lang_latest_evento
        font: FluTextStyle.Title
        Layout.topMargin: 20
        Layout.leftMargin: 20
    }

    GridView {
        topMargin: 10
        Layout.fillWidth: true
        implicitHeight: contentHeight
        cellHeight: 160
        cellWidth: 292
        interactive: false
        delegate: com_item2
        model: LatestEventoModel
    }

    Component {
        id: com_item
        Item {
            Layout.topMargin: 10
            width: 280
            height: 135
            FluArea {
                radius: 8
                width: 280
                height: 135
                anchors.centerIn: parent
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
                FluRectangle {
                    id: item_icon
                    height: 115
                    width: 115
                    radius: [6, 6, 6, 6]
                    shadow: false
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluImage {
                        anchors.fill: parent
                        source: model.image
                        fillMode: Image.PreserveAspectCrop
                    }
                }

                FluText {
                    id: item_title
                    text: model.title
                    font: FluTextStyle.Subtitle
                    elide: Text.ElideRight
                    maximumLineCount: 1
                    anchors {
                        left: item_icon.right
                        leftMargin: 12
                        top: item_icon.top
                        right: parent.right
                        rightMargin: 5
                    }
                }

                Row {
                    id: item_time
                    spacing: 5
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_title.bottom
                        topMargin: 10
                    }
                    FluIcon {
                        iconSource: FluentIcons.EmojiTabFavorites
                    }
                    FluText {
                        text: model.time
                        color: FluColors.Grey120
                        width: 110
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                        font: FluTextStyle.Caption
                        maximumLineCount: 2
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    id: item_location
                    spacing: 5
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_time.bottom
                        topMargin: 5
                    }
                    FluIcon {
                        iconSource: FluentIcons.POI
                    }
                    FluText {
                        text: model.location
                        width: 110
                        color: FluColors.Grey120
                        font: FluTextStyle.Caption
                        elide: Text.ElideRight
                        maximumLineCount: 1
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    id: item_department
                    spacing: 5
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_location.bottom
                        topMargin: 5
                    }
                    FluIcon {
                        iconSource: FluentIcons.EMI
                    }
                    FluText {
                        text: model.department
                        width: 110
                        color: FluColors.Grey120
                        elide: Text.ElideRight
                        font: FluTextStyle.Caption
                        maximumLineCount: 1
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    propagateComposedEvents: true
                    onClicked: {
                        EventoHelper.id = model.id
                        MainWindow.window.pushPage(
                                    "qrc:/qml/page/T_EventInfo.qml")
                    }
                }
            }
        }
    }

    Component {
        id: com_item2
        Item {
            Layout.topMargin: 10
            width: 280
            height: 140
            FluArea {
                radius: 8
                width: 280
                height: 140
                anchors.centerIn: parent
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
                FluRectangle {
                    id: item_icon
                    height: 115
                    width: 115
                    radius: [6, 6, 6, 6]
                    shadow: false
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluImage {
                        anchors.fill: parent
                        source: model.url
                        fillMode: Image.PreserveAspectCrop
                    }
                }

                FluText {
                    id: item_title
                    text: model.title
                    font: FluTextStyle.Subtitle
                    elide: Text.ElideRight
                    maximumLineCount: 1
                    anchors {
                        left: item_icon.right
                        leftMargin: 12
                        top: item_icon.top
                        right: parent.right
                        rightMargin: 5
                    }
                }

                FluText {
                    id: item_time
                    anchors {
                        left: item_title.left
                        top: item_title.bottom
                        right: parent.right
                        rightMargin: 20
                        topMargin: 10
                    }
                    text: model.time
                    color: FluColors.Grey120
                    width: 110
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    maximumLineCount: 2
                }

                FluText {
                    id: item_department
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_time.bottom
                        topMargin: 5
                    }
                    text: model.department
                    color: FluColors.Grey120
                    elide: Text.ElideRight
                    font: FluTextStyle.Caption
                    maximumLineCount: 1
                }

                FluText {
                    id: item_desc
                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_department.bottom
                        topMargin: 8
                    }
                    text: model.description
                    color: FluColors.Grey120
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                    font: FluTextStyle.Caption
                    maximumLineCount: 2
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
        }
    }
}
