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

    property int deleteMode: 0
    property int isDirShowMode: 0
    property string deletedUrl: ""
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

    Connections {
        target: GalleryController
        function onDeleteImgRequestSuccessEvent() {
            showSuccess("删除成功")
            galleryPage.statusMode = FluStatusViewType.Success
            trySwitchImgPage(tree_view.currentName, img_pagination.pageCurrent)
            //loading_cover.visible = false
            //loading_mouse_cover.visible = false
        }
    }

    Connections {
        target: GalleryController
        function onDeleteImgRequestErrorEvent(message) {
            showError(message)
            galleryPage.statusMode = FluStatusViewType.Success
            //loading_cover.visible = false
            //loading_mouse_cover.visible = false
        }
    }

    function loadGalleryUrlListInfo() {
        statusMode = FluStatusViewType.Loading
        GalleryController.loadGalleryDirJson()
        galleryDirJson = GalleryHelper.dirJson
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

    function trySwitchDir(dirName) {
        img_pagination.visible = false
        trySwitchImgPage(dirName, 1)
        img_pagination.pageCurrent = 1
    }

    function trySwitchImgPage(dirName, pageNumber) {
        inside_page.visible = true
        inside_page.statusMode = FluStatusViewType.Loading
        GalleryController.loadGalleryDirImgInfo(dirName, pageNumber)
        var dirJson = JSON.parse(GalleryHelper.dirImgInfo)
        img_pagination.itemCount = dirJson.count
        img_review.model = dirJson.url
    }

    FluText {
        id: text_title
        font: FluTextStyle.Title
        text: "图库"
        height: contentHeight
        padding: 0
    }

    FluArea {
        id: top_area
        height: 38
        color: Qt.rgba(0, 0, 0, 0)
        border.color: Qt.rgba(0, 0, 0, 0)
        width: galleryPage.width - galleryPage.rightPadding - galleryPage.leftPadding

        FluIconButton {
            id: delete_button
            iconSource: FluentIcons.Delete
            pressedColor: deleteMode ? (FluTheme.dark ? Qt.rgba(
                                                            175 / 255, 0, 0,
                                                            0.6) : Qt.rgba(255 / 255, 73 / 255, 73 / 255, 0.9)) : (FluTheme.dark ? Qt.rgba(1, 1, 1, 0.06) : Qt.rgba(0, 0, 0, 0.06))
            normalColor: deleteMode ? (FluTheme.dark ? Qt.rgba(
                                                           175 / 255, 0, 0,
                                                           0.9) : Qt.rgba(255 / 255, 73 / 255, 73 / 255, 0.6)) : (FluTheme.dark ? Qt.rgba(0, 0, 0, 0) : Qt.rgba(0, 0, 0, 0))
            hoverColor: deleteMode ? (FluTheme.dark ? Qt.rgba(
                                                          175 / 255, 0, 0,
                                                          0.75) : Qt.rgba(255 / 255, 73 / 255, 73 / 255, 0.75)) : (FluTheme.dark ? Qt.rgba(1, 1, 1, 0.03) : Qt.rgba(0, 0, 0, 0.03))
            anchors.right: parent.right
            onClicked: {
                if (deleteMode == 0) {
                    deleteMode = 1
                    showMessage("切换到删除模式")
                } else {
                    deleteMode = 0
                    showMessage("退出删除模式")
                }
            }
        }

        FluIconButton {
            id: addgalleryButton
            iconSource: FluentIcons.Add
            anchors {
                top: delete_button.top
                right: delete_button.left
                rightMargin: 10
            }
            onClicked: {
                showSuccess("TODO:触发添加页面")
                //MainWindow.window.pushPage("qrc:/qml/page/T_PictureSelection.qml")
            }
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
            height: galleryPage.height - galleryPage.topPadding
                    - galleryPage.bottomPadding - top_area.Layout.topMargin
                    - top_area.Layout.bottomMargin - top_area.height - text_title.height
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
                                   if (isStart == 0
                                       || currentName !== dirName) {
                                       //showSuccess("TODO:点击了dir id: " + dirName)
                                       currentName = dirName
                                       if (isStart == 0) {
                                           isStart = 1
                                       }
                                       trySwitchDir(dirName)
                                   }
                               }
            }
        }

        FluArea {
            id: second_area
            color: Qt.rgba(0, 0, 0, 0)
            border.color: Qt.rgba(0, 0, 0, 0)
            width: galleryPage.width - galleryPage.rightPadding
                   - galleryPage.leftPadding - first_area.width - parent.spacing
            height: galleryPage.height - galleryPage.topPadding
                    - galleryPage.bottomPadding - top_area.Layout.topMargin
                    - top_area.Layout.bottomMargin - top_area.height - text_title.height
            FluArea {
                color: Qt.rgba(0, 0, 0, 0)
                border.color: Qt.rgba(0, 0, 0, 0)
                id: second_area_head
                anchors.top: parent.top
                width: parent.width
                height: parent.height - 60
                FluScrollablePage {
                    id: inside_page
                    emptyText: "请打开左侧目录获取信息"
                    statusMode: FluStatusViewType.Empty
                    anchors.fill: parent
                    leftPadding: 0
                    rightPadding: 0
                    topPadding: 0
                    bottomPadding: 0

                    onErrorClicked: {
                        trySwitchImgPage(tree_view.currentName,
                                         img_pagination.pageCurrent)
                    }

                    GridView {
                        property int spacing: 20
                        //spacing: 20
                        //Spacing is not its attribute, but it has been incorporated into the calculation here
                        id: img_review
                        Layout.fillWidth: true
                        implicitHeight: contentHeight
                        cellWidth: second_area.width > 780 ? ((second_area.width
                                                               - 3 * spacing) / 4) : (160 + spacing)
                        cellHeight: (cellWidth - 20) / 4 * 3 + spacing
                        interactive: false
                        delegate: com_item
                    }
                }
            }
            FluArea {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 50
                color: Qt.rgba(0, 0, 0, 0)
                border.color: Qt.rgba(0, 0, 0, 0)
                FluPagination {
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
                                       trySwitchImgPage(tree_view.currentName,
                                                        page)
                                   }
                }
            }
        }
    }

    Component {
        id: com_item
        Item {
            width: img_review.cellWidth - img_review.spacing
            height: img_review.cellHeight - img_review.spacing
            FluRectangle {
                anchors.fill: parent
                radius: [6, 6, 6, 6]
                FluImage {
                    anchors.fill: parent
                    source: model.modelData
                    fillMode: Image.PreserveAspectCrop
                    FluIconButton {
                        id: delete_button
                        visible: deleteMode
                        anchors.fill: parent
                        pressedColor: Qt.rgba(175 / 255, 0, 0, 0.7)
                        hoverColor: Qt.rgba(175 / 255, 0, 0, 0.5)
                        anchors.right: parent.right
                        onClicked: {
                            delete_img_dialog.open()
                        }
                    }
                }
            }
            FluContentDialog {
                id: delete_img_dialog
                title: "删除图片"
                message: "是否确定删除图片？"
                buttonFlags: FluContentDialogType.NegativeButton
                             | FluContentDialogType.PositiveButton
                negativeText: "取消"
                positiveText: "确定"
                onPositiveClicked: {
                    //showSuccess("TODO:触发向后端发送删除图片 url: " + model.modelData)
                    //loading_cover.visible = true
                    //loading_mouse_cover.visible = true
                    galleryPage.statusMode = FluStatusViewType.Loading
                    GalleryController.deleteImgRequest(model.modelData)
                }
            }
        }
    }

    /*
    FluStatusView{
        id: loading_cover
        visible: false
        anchors.fill: parent
        color: FluTheme.dark ? Qt.rgba(0,0,0,0.5) : Qt.rgba(1,1,1,0.5)
        statusMode: FluStatusViewType.Loading
        Rectangle{
            anchors.fill: parent
            color:FluTheme.primaryColor.dark
        }
    }
    MouseArea{
        id: loading_mouse_cover
        visible: false
        anchors.fill: parent
    }
    */
}
