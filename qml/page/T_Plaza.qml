import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollablePage {
    id: page

    property var arr: []

    signal listReady()

    function loadPlazaInfo() {
        statusMode = FluStatusViewType.Loading;
        PlazaController.loadPlazaInfo();
    }

    function loadHomeSlide() {
        PlazaController.loadHomeSlide();
    }

    launchMode: FluPageType.SingleTask
    onErrorClicked: {
        loadPlazaInfo();
    }
    errorButtonText: lang.lang_reload
    loadingText: lang.lang_loading
    Component.onCompleted: {
        loadPlazaInfo();
        loadHomeSlide();
    }

    Connections {
        function onLoadPlazaSuccessEvent() {
            statusMode = FluStatusViewType.Success;
        }

        target: PlazaController
    }

    Connections {
        function onLoadPlazaErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusViewType.Error;
        }

        target: PlazaController
    }

    Loader {
        id: loader

        sourceComponent: undefined
    }

    Connections {
        function onLoadHomeSlideSuccessEvent() {
            arr = [];
            loader.sourceComponent = rep_com;
            page.listReady();
        }

        target: PlazaController
    }

    Component {
        id: rep_com

        Repeater {
            id: rep

            model: SlideModel

            Item {
                Component.onCompleted: {
                    arr.push({
                        "url": url,
                        "link": link,
                        "title": title
                    });
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
        indicatorGravity: Qt.AlignTop | Qt.AlignHCenter
        loopTime: 4000

        Connections {
            function onListReady() {
                carousel.model = arr;
                loader.sourceComponent = undefined;
            }

            target: page
        }

        delegate: Item {
            height: carousel.height
            width: carousel.width

            FluClip {
                anchors.fill: parent
                radius: [10, 10, 10, 10]

                FluImage {
                    anchors.fill: parent
                    source: model.url
                    asynchronous: true
                    cache: true
                    fillMode: Image.PreserveAspectCrop
                }

            }

            Rectangle {
                height: 40
                width: parent.width
                radius: 10
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
                    PlazaController.openUrl(model.link);
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
                            if (item_mouse.containsMouse)
                                return Qt.rgba(1, 1, 1, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        } else {
                            if (item_mouse.containsMouse)
                                return Qt.rgba(0, 0, 0, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        }
                    }
                }

                FluClip {
                    id: item_icon

                    height: 115
                    width: 115
                    radius: [6, 6, 6, 6]

                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }

                    FluImage {
                        anchors.fill: parent
                        source: image
                        fillMode: Image.PreserveAspectCrop
                    }

                }

                FluText {
                    id: item_title

                    text: title
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
                        text: time
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
                        text: location
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
                        text: department
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
                        EventoHelper.id = id;
                        MainWindow.window.pushPage("qrc:/qml/page/T_EventInfo.qml");
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
                            if (item_mouse.containsMouse)
                                return Qt.rgba(1, 1, 1, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        } else {
                            if (item_mouse.containsMouse)
                                return Qt.rgba(0, 0, 0, 0.03);

                            return Qt.rgba(0, 0, 0, 0);
                        }
                    }
                }

                FluClip {
                    id: item_icon

                    height: 115
                    width: 115
                    radius: [6, 6, 6, 6]

                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }

                    FluImage {
                        anchors.fill: parent
                        source: url
                        fillMode: Image.PreserveAspectCrop
                    }

                }

                FluText {
                    id: item_title

                    text: title
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

                    text: time
                    color: FluColors.Grey120
                    width: 110
                    wrapMode: Text.WordWrap
                    font: FluTextStyle.Caption
                    maximumLineCount: 2

                    anchors {
                        left: item_title.left
                        top: item_title.bottom
                        right: parent.right
                        rightMargin: 20
                        topMargin: 10
                    }

                }

                FluText {
                    id: item_department

                    text: department
                    color: FluColors.Grey120
                    elide: Text.ElideRight
                    font: FluTextStyle.Caption
                    maximumLineCount: 1

                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_time.bottom
                        topMargin: 5
                    }

                }

                FluText {
                    id: item_desc

                    text: description
                    color: FluColors.Grey120
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                    font: FluTextStyle.Caption
                    maximumLineCount: 2

                    anchors {
                        left: item_title.left
                        right: parent.right
                        rightMargin: 20
                        top: item_department.bottom
                        topMargin: 8
                    }

                }

                MouseArea {
                    id: item_mouse

                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        EventoHelper.id = id;
                        MainWindow.window.pushPage("qrc:/qml/page/T_EventInfo.qml");
                    }
                }

            }

        }

    }

}
