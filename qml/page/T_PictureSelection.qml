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

    property string galleryDirJson

    onErrorClicked: {
        loadGalleryUrlListInfo()
    }

    Component.onCompleted: {
         loadGalleryUrlListInfo()
    }

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

    Connections {
        target: GalleryController
        function onLoadGalleryDirImgInfoSuccessEvent() {
            img_pagination.visible = true
            inside_page.statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: GalleryController
        function onLoadGalleryDirImgInfoErrorEvent(message) {
            inside_page.errorText = message
            inside_page.statusMode = FluStatusViewType.Error
        }
    }

    function loadGalleryUrlListInfo() {
        statusMode = FluStatusViewType.Loading
        galleryDirJson = GalleryController.loadGalleryUrlList() //这里controller刻意少写了一个Info
        tree_view.updateData(createDir())
    }

    function createDir() {
        var galleryDirArr = []
        var json = JSON.parse(galleryDirJson)
        for (var i = 0; i < json.length; ++i) {
            galleryDirArr.push(tree_view.createItem(json[i].name, true, [], {
                                                        "name": json[i].name
                                                    }))
        }
        return galleryDirArr
    }

    function trySwitchDir(dirName){
        img_pagination.visible = false
        trySwitchImgPage(dirName, 1)
        img_pagination.pageCurrent = 1
    }

    function trySwitchImgPage(dirName, pageNumber){
        inside_page.visible = true
        inside_page.statusMode = FluStatusViewType.Loading
        var dirJson = JSON.parse(GalleryController.loadGalleryDirImgInfo(dirName, pageNumber))
        img_pagination.itemCount = dirJson.count
        eventCard.model = dirJson.url
    }

    FluText{
        id:text_title
        font: FluTextStyle.Title
        text: "图片选择"
        height: contentHeight
        padding: 0
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
                    text_title.height
            FluTreeView {
                property string currentName
                property int isStart: 0
                id: tree_view
                width: 175
                height: parent.height - parent.paddings * 2
                selectionMode: FluTreeViewType.Single
                anchors.fill: parent
                onItemClicked: item => {
                                   var dirName = item.data.name
                                   if(isStart == 0 || currentName !== dirName){
                                       //showSuccess("TODO:点击了dir id: " + dirName)
                                       currentName = dirName
                                       if(isStart == 0){
                                           isStart = 1
                                       }
                                       trySwitchDir(dirName)
                                   }

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
                    text_title.height
            FluArea{
                color: Qt.rgba(0,0,0,0)
                border.color: Qt.rgba(0,0,0,0)
                id: second_area_head
                anchors.top: parent.top
                width: parent.width
                height: parent.height - 60
                FluScrollablePage{
                    id: inside_page
                    emptyText: "请打开左侧目录获取信息"
                    statusMode: FluStatusViewType.Empty
                    anchors.fill: parent
                    leftPadding: 0
                    rightPadding: 0
                    topPadding: 0
                    bottomPadding: 0

                    onErrorClicked: {
                        trySwitchImgPage(tree_view.currentName, img_pagination.pageCurrent)
                    }

                    GridView {
                        property int spacing: 20
                        //spacing: 20
                        //Spacing is not its attribute, but it has been incorporated into the calculation here
                        id: eventCard
                        Layout.fillWidth: true
                        implicitHeight: contentHeight
                        cellWidth: second_area.width > 780 ? ((second_area.width - 3 * spacing) / 4 ) : (160 + spacing)
                        cellHeight: (cellWidth - 20) / 4 * 3 + spacing
                        interactive: false
                        delegate: com_item
                    }
                }
            }
            FluArea{
                anchors.bottom: parent.bottom
                width: parent.width
                height: 50
                color: Qt.rgba(0,0,0,0)
                border.color: Qt.rgba(0,0,0,0)
                    FluPagination{
                        id: img_pagination
                        visible: false
                        pageCurrent: 1
                        itemCount: 1000
                        __itemPerPage: 20
                        //visible: (parent.width > 450) ? true : false
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            left: parent.left
                        }
                        onRequestPage: (page, size) => {
                                           //showSuccess("切换到"+tree_view.currentName+"目录第"+page+"页")
                                           trySwitchImgPage(tree_view.currentName, page)
                                       }
                    }
            }
        }
    }


    Component {
        id: com_item
        Item {
            width: eventCard.cellWidth - eventCard.spacing
            height: eventCard.cellHeight - eventCard.spacing
            FluRectangle{
                anchors.fill: parent
                shadow: false
                radius: [6,6,6,6]
                FluImage {
                    anchors.fill: parent
                    source: model.modelData
                    fillMode: Image.PreserveAspectCrop
                    FluIconButton {
                        id: delete_button
                        visible: true
                        anchors.fill: parent
                        pressedColor: Qt.rgba(175/255,0,0,0.7)
                        hoverColor: Qt.rgba(175/255,0,0,0.5)
                        anchors.right: parent.right
                        onClicked: {
                            showSuccess("点击图片")
                        }
                    }
                }
            }
        }
    }
}
