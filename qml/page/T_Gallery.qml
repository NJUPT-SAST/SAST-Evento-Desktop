import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: galleryPage
    launchMode: FluPageType.SingleTask
    //title: "图库"

    property string galleryJson

    onErrorClicked: {
        loadGalleryUrlListInfo()
    }

    Component.onCompleted: {
         loadGalleryUrlListInfo()
    }

    function loadGalleryUrlListInfo() {
        statusMode = FluStatusViewType.Loading
        galleryJson = GalleryController.loadGalleryUrlList() //这里controller刻意少写了一个Info
        //console.log(galleryJson)
        tree_view.updateData(createOrg())
    }

    //function loadGalleryDirInfo() {
    //    GalleryController.loadGalleryUrlList()
    //}

    Connections {
        target: GalleryController
        function onLoadGalleryUrlListSuccessEvent() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: GalleryController
        function onLoadGalleryUrlListErrorEvent(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    //loadGalleryUrlListErrorEvent

    function createOrg() {
        var departmentArr = []
        var json = JSON.parse(galleryJson)
        for (var i = 0; i < json.length; ++i) {
            departmentArr.push(tree_view.createItem(json[i].name, true, [], {
                                                        "id": json[i].id
                                                    }))
        }
        return departmentArr
    }

    FluText{
        id:text_title
        font: FluTextStyle.Title
        text: "图库"
        height: contentHeight
        padding: 0
        anchors{
            top: parent.top
            topMargin: galleryPage.topPadding
            left: parent.left
            right: parent.right
            leftMargin: galleryPage.leftPadding
            rightMargin: galleryPage.rightPadding
        }
    }

    FluIconButton {
        id: addgalleryButton
        iconSource: FluentIcons.Add
        Layout.alignment: Qt.AlignRight
        onClicked: {

            //MainWindow.window.pushPage("qrc:/qml/page/T_SlideManagementEdit.qml")
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 20

        FluArea {
            //color: Qt.rgba(0,0,0,0)
            id: first_area
            paddings: 10
            width: 200
            Layout.alignment: Qt.AlignTop
            height: galleryPage.height -
                    galleryPage.topPadding -
                    galleryPage.bottomPadding -
                    addgalleryButton.Layout.topMargin -
                    addgalleryButton.Layout.bottomMargin -
                    addgalleryButton.height -
                    text_title.height
            FluTreeView {
                id: tree_view
                width: 175
                height: parent.height - parent.paddings * 2
                selectionMode: FluTreeViewType.Single
                anchors.fill: parent
                onItemClicked: item => {}

                Component.onCompleted: {

                }
            }
        }

        FluArea{
            id: second_area
            color: Qt.rgba(0,0,0,0)
            border.color: Qt.rgba(0,0,0,0)
            width: galleryPage.width -
                   galleryPage.rightPadding -
                   galleryPage.leftPadding -
                   first_area.width -
                   parent.spacing
            height: galleryPage.height -
                    galleryPage.topPadding -
                    galleryPage.bottomPadding -
                    addgalleryButton.Layout.topMargin -
                    addgalleryButton.Layout.bottomMargin -
                    addgalleryButton.height -
                    text_title.height
            FluArea{
                color: Qt.rgba(0,0,0,0)
                //border.color: Qt.rgba(0,0,0,0)
                id: second_area_head
                anchors.top: parent.top
                width: parent.width
                height: parent.height - 60
            }
            FluArea{
                anchors.bottom: parent.bottom
                width: parent.width
                height: 50
                color: Qt.rgba(0,0,0,0)
                border.color: Qt.rgba(0,0,0,0)
                    FluPagination{
                        pageCurrent: 1
                        itemCount: 1000
                        pageButtonCount: 4
                        visible: (parent.width > 450) ? true : false
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            left: parent.left
                        }
                    }
                    FluFilledButton{
                        text: "右拉显示页数与选定"
                        visible: (parent.width > 450) ? false : true
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            left: parent.left
                        }
                        onClicked: {
                            showWarning("点什么点，都快被你挤坏了QAQ")
                        }
                    }
                    FluFilledButton {
                        visible: (parent.width > 450) ? true : false
                        text: "选定"
                        onClicked: {
                            //showWarning("这是一个Warning样式的InfoBar")
                        }
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: parent.right
                        }
                    }

            }
        }
            /*GridView {
                id: eventCard
                Layout.topMargin: 10
                Layout.rightMargin: 10
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                implicitHeight: gridHeight()
                cellHeight: 150
                cellWidth: 292
                interactive: false
                delegate: com_item
                model: EventoBriefModel
            }*/
    }
}
