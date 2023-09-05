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

    property int delete_mode : 0
    property string deleted_url: ""
    property string galleryDirJson
    property string galleryImgJson: "[\"1\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",
                                      \"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\",\"2\"]"

    onErrorClicked: {
        loadGalleryUrlListInfo()
    }

    Component.onCompleted: {
         loadGalleryUrlListInfo()
    }

    function loadGalleryUrlListInfo() {
        statusMode = FluStatusViewType.Loading
        galleryDirJson = GalleryController.loadGalleryUrlList() //这里controller刻意少写了一个Info
        tree_view.updateData(createDir())
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

    Connections {
        target: GalleryController
        function onLoadGalleryUrlListSuccessEvent() {
            dirImgStatus = FluStatusViewType.Success
        }
    }

    Connections {
        target: GalleryController
        function onLoadGalleryUrlListErrorEvent(message) {
            dirImgMsg = message
            dirImgStatus = FluStatusViewType.Error
        }
    }

    function createDir() {
        var galleryDirArr = []
        var json = JSON.parse(galleryDirJson)
        for (var i = 0; i < json.length; ++i) {
            galleryDirArr.push(tree_view.createItem(json[i].name, true, [], {
                                                        "id": json[i].id
                                                    }))
        }
        console.log(galleryDirArr)
        return galleryDirArr
    }

    function createImgList() {
        return JSON.parse(galleryImgJson)
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

    FluArea{
        id: top_area
        height: 38
        color: Qt.rgba(0,0,0,0)
        border.color: Qt.rgba(0,0,0,0)
        width: galleryPage.width -
               galleryPage.rightPadding -
               galleryPage.leftPadding

        FluIconButton {
            id: delete_button
            iconSource: FluentIcons.Delete
            pressedColor: delete_mode ? (FluTheme.dark ? Qt.rgba(175/255,0,0,0.6) : Qt.rgba(255/255,73/255,73/255,0.9)) :
                                        (FluTheme.dark ? Qt.rgba(1,1,1,0.06) : Qt.rgba(0,0,0,0.06))
            normalColor: delete_mode ? (FluTheme.dark ? Qt.rgba(175/255,0,0,0.9) : Qt.rgba(255/255,73/255,73/255,0.6)):
                                       (FluTheme.dark ? Qt.rgba(0,0,0,0) : Qt.rgba(0,0,0,0))
            hoverColor:delete_mode ? (FluTheme.dark ? Qt.rgba(175/255,0,0,0.75) : Qt.rgba(255/255,73/255,73/255,0.75)):
                                     (FluTheme.dark ? Qt.rgba(1,1,1,0.03) : Qt.rgba(0,0,0,0.03))
            anchors.right: parent.right
            onClicked: {
                if(delete_mode == 0){
                    delete_mode = 1
                    showSuccess("切换到删除模式")
                }else {
                    delete_mode = 0
                    showSuccess("退出删除模式")
                }
            }
        }

        FluIconButton {
            id: addgalleryButton
            iconSource: FluentIcons.Add
            anchors{
                top: delete_button.top
                right: delete_button.left
                rightMargin: 10
            }
            onClicked: {
                showSuccess("TODO:触发添加页面")
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
            height: galleryPage.height -
                    galleryPage.topPadding -
                    galleryPage.bottomPadding -
                    top_area.Layout.topMargin -
                    top_area.Layout.bottomMargin -
                    top_area.height -
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
                    top_area.Layout.topMargin -
                    top_area.Layout.bottomMargin -
                    top_area.height -
                    text_title.height
            FluArea{
                color: Qt.rgba(0,0,0,0)
                //border.color: Qt.rgba(0,0,0,0)
                id: second_area_head
                anchors.top: parent.top
                width: parent.width
                height: parent.height - 60

                FluScrollablePage{
                    id: inside_page
                    anchors.fill: parent
                    leftPadding: 0
                    rightPadding: 0
                    topPadding: 0
                    bottomPadding: 0
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
                        model: createImgList()
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
                        pageCurrent: 1
                        itemCount: 1000
                        pageButtonCount: 4
                        //visible: (parent.width > 450) ? true : false
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            left: parent.left
                        }
                    }
                    /*
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
                        onClicked: {}
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: parent.right
                        }
                    }
                    */
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
                    source: "qrc:/res/image/banner_3.png"
                    fillMode: Image.PreserveAspectCrop
                    FluIconButton {
                        id: delete_button
                        visible: delete_mode
                        anchors.fill: parent
                        pressedColor: Qt.rgba(175/255,0,0,0.7)
                        hoverColor: Qt.rgba(175/255,0,0,0.5)
                        anchors.right: parent.right
                        onClicked: {
                            delete_img_dialog.open()
                        }
                    }
                }
            }
            FluContentDialog{
                    id:delete_img_dialog
                    title:"删除图片"
                    message:"是否确定删除图片？"
                    buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
                    negativeText:"取消"
                    positiveText:"确定"
                    onPositiveClicked:{
                        showSuccess("TODO:触发向后端发送删除图片 url: " + model.modelData)
                    }
            }
        }
    }
}
