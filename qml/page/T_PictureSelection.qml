import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

//This qml is same to T_Gallery.qml. Use Gallery_controller Together
FluScrollablePage {
    id: galleryPage

    property bool isSelectedDir: false
    property string galleryDirJson
    property int maxSelectionNumber: GalleryHelper.maxNum
    property var selectedUrlList: []

    function refreshPageSelection() {
        for (var i = 0; i < img_review.count; i++) {
            img_review.itemAtIndex(i).refreshSelfSelection();
        }
    }

    function loadGalleryUrlListInfo() {
        statusMode = FluStatusViewType.Loading;
        GalleryController.loadGalleryDirJson();
        galleryDirJson = GalleryHelper.dirJson;
        tree_view.updateData(createDir());
    }

    function createDir() {
        var galleryDirArr = [];
        var json = JSON.parse(galleryDirJson);
        for (var i = 0; i < json.length; ++i) {
            galleryDirArr.push(tree_view.createItem(json[i].name, true, [], {
                "name": json[i].name
            }));
        }
        return galleryDirArr;
    }

    function trySwitchDir(dirName) {
        img_pagination.visible = false;
        trySwitchImgPage(dirName, 1);
        img_pagination.pageCurrent = 1;
    }

    function trySwitchImgPage(dirName, pageNumber) {
        inside_page.visible = true;
        inside_page.statusMode = FluStatusViewType.Loading;
        GalleryController.loadGalleryDirImgInfo(dirName, pageNumber);
        var dirJson = JSON.parse(GalleryHelper.dirImgInfo);
        img_pagination.itemCount = dirJson.count;
        img_review.model = dirJson.url;
    }

    function returnPage() {
        MainWindow.window.pushPage(maxSelectionNumber === 1 ? "qrc:/qml/page/T_SlideManagementEdit.qml" : "qrc:/qml/page/T_EventoEdit.qml");
    }

    launchMode: FluPageType.SingleTask
    onErrorClicked: {
        loadGalleryUrlListInfo();
    }
    Component.onCompleted: {
        loadGalleryUrlListInfo();
    }

    Connections {
        function onLoadGalleryUrlListSuccessEvent() {
            statusMode = FluStatusViewType.Success;
        }

        target: GalleryController
    }

    Connections {
        function onLoadGalleryUrlListErrorEvent(message) {
            errorText = message;
            statusMode = FluStatusViewType.Error;
        }

        target: GalleryController
    }

    Connections {
        function onLoadGalleryDirImgInfoSuccessEvent() {
            img_pagination.visible = true;
            inside_page.statusMode = FluStatusViewType.Success;
        }

        target: GalleryController
    }

    Connections {
        function onLoadGalleryDirImgInfoErrorEvent(message) {
            inside_page.errorText = message;
            inside_page.statusMode = FluStatusViewType.Error;
        }

        target: GalleryController
    }

    FluText {
        id: text_title

        font: FluTextStyle.Title
        text: "图片选择"
        height: contentHeight
        padding: 0
    }

    FluArea {
        id: top_area

        height: 38
        color: Qt.rgba(0, 0, 0, 0)
        border.color: Qt.rgba(0, 0, 0, 0)
        width: galleryPage.width - galleryPage.rightPadding - galleryPage.leftPadding

        FluFilledButton {
            id: selection_finished

            text: "选定"
            anchors.right: parent.right
            onClicked: {
                GalleryHelper.urlList = selectedUrlList;
                returnPage();
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
            height: galleryPage.height - galleryPage.topPadding - galleryPage.bottomPadding - top_area.Layout.topMargin - top_area.Layout.bottomMargin - top_area.height - text_title.height

            FluTreeView {
                id: tree_view

                property string currentName
                property int isStart: 0

                width: 175
                height: parent.height - parent.paddings * 2
                selectionMode: FluTreeViewType.Single
                anchors.fill: parent
                onItemClicked: (item) => {
                    var dirName = item.data.name;
                    if (isStart == 0 || currentName !== dirName) {
                        //showSuccess("TODO:点击了dir id: " + dirName)
                        currentName = dirName;
                        if (isStart == 0)
                            isStart = 1;

                        trySwitchDir(dirName);
                    }
                }
            }

        }

        FluArea {
            id: second_area

            color: Qt.rgba(0, 0, 0, 0)
            border.color: Qt.rgba(0, 0, 0, 0)
            width: galleryPage.width - galleryPage.rightPadding - galleryPage.leftPadding - first_area.width - parent.spacing
            height: galleryPage.height - galleryPage.topPadding - galleryPage.bottomPadding - top_area.Layout.topMargin - top_area.Layout.bottomMargin - top_area.height - text_title.height

            FluArea {
                id: second_area_head

                color: Qt.rgba(0, 0, 0, 0)
                border.color: Qt.rgba(0, 0, 0, 0)
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
                        trySwitchImgPage(tree_view.currentName, img_pagination.pageCurrent);
                    }

                    GridView {
                        //spacing: 20
                        //Spacing is not its attribute, but it has been incorporated into the calculation here
                        id: img_review

                        property int spacing: 20

                        Layout.fillWidth: true
                        implicitHeight: contentHeight
                        cellWidth: second_area.width > 780 ? ((second_area.width - 3 * spacing) / 4) : (160 + spacing)
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
                    onRequestPage: (page, size) => {
                        //showSuccess("切换到"+tree_view.currentName+"目录第"+page+"页")
                        trySwitchImgPage(tree_view.currentName, page);
                    }

                    //visible: (parent.width > 450) ? true : false
                    anchors {
                        bottom: parent.bottom
                        bottomMargin: 10
                        left: parent.left
                    }

                }

            }

        }

    }

    Component {
        id: com_item

        Item {
            property string item_img_url: model.modelData

            function refreshSelfSelection() {
                //img_checkbox.visible = selectedUrlList.indexOf(item_img_url) > -1
                img_checkbox.checked = selectedUrlList.indexOf(item_img_url) > -1;
                img_checkbox.disabled = !img_checkbox.checked && selectedUrlList.length >= maxSelectionNumber;
                delete_button.normalColor = (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0);
                delete_button.pressedColor = (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0.5);
                delete_button.hoverColor = (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0.3);
            }

            width: img_review.cellWidth - img_review.spacing
            height: img_review.cellHeight - img_review.spacing

            FluRectangle {
                id: item_rectangle

                anchors.fill: parent
                radius: [6, 6, 6, 6]

                FluImage {
                    id: item_img

                    anchors.fill: parent
                    source: item_img_url
                    fillMode: Image.PreserveAspectCrop

                    FluCheckBox {
                        id: img_checkbox

                        //visible: selectedUrlList.indexOf(item_img_url) > -1
                        disableColor: Qt.rgba(101 / 255, 101 / 255, 101 / 255, 1)
                        checked: selectedUrlList.indexOf(item_img_url) > -1
                        disabled: !checked && selectedUrlList.length >= maxSelectionNumber
                    }

                    FluIconButton {
                        id: delete_button

                        visible: true
                        anchors.fill: parent
                        normalColor: (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0)
                        pressedColor: (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0.5)
                        hoverColor: (selectedUrlList.length >= maxSelectionNumber) && !img_checkbox.checked ? Qt.rgba(0, 0, 0, 0.6) : Qt.rgba(0, 0, 0, 0.3)
                        anchors.right: parent.right
                        onClicked: {
                            if ((selectedUrlList.length >= maxSelectionNumber) && (!img_checkbox.checked)) {
                                showError("抱歉，只能选择" + maxSelectionNumber + "张图片哦");
                            } else {
                                //console.log(selectedUrlList)

                                if (img_checkbox.checked)
                                    selectedUrlList = selectedUrlList.filter(function(item) {
                                        return item !== item_img_url;
                                    });
                                else
                                    selectedUrlList.push(item_img_url);
                                refreshPageSelection();
                            }
                        }
                    }

                }

            }

        }

    }

}
