import "../component"
import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollableStatusPage {
    // title: "Location Management"

    id: locationPage

    property var locationSelectData: []
    property var locationListData: []
    // item信息
    property string forceItemName: ""
    property int forceItemId: -1
    property int editLocationId: -1 // 判断是否存在编辑
    property bool isNewLocation: false // 判断是否是新地点
    // 父节点选择信息
    property string selectParentName: ""
    property int selectParentId: -1

    signal listReady()
    signal changeParent()

    function parseJSON(data) {
        var res = [];
        if (Array.isArray(data)) {
            for (var i = 0; i < data.length; i++) {
                var item = data[i];
                var children = [];
                var isLeaf = false;
                if (item.children && Array.isArray(item.children))
                    children = parseJSON(item.children);
                else
                    isLeaf = true;
                res.push(locationTree.createItem(item.name, isLeaf, children, {
                    "id": item.id,
                    "name": item.name
                }));
            }
        } else {
            res.push(locationTree.createItem(item.name, true, [], {
                "id": data.id,
                "name": data.name
            }));
        }
        return res;
    }

    function loadLocationInfo(locationJson) {
        locationListData = parseJSON(locationJson);
        locationSelectData.push(locationTree.createItem("\\", false, locationListData, {
            "id": 0,
            "name": "\\"
        }));
        listReady();
    }

    function loadAllLocation() {
        statusMode = FluStatusLayoutType.Loading;
        locationSelectData = [];
        locationListData = [];
        loadLocationInfo(JSON.parse(LocationManagementController.loadAllLocation()));
    }

    function submitLoactionChange(id, name, parentId, isAdd) {
        statusMode = FluStatusLayoutType.Loading;
        if (isAdd)
            LocationManagementController.addLocation(name, parentId);
        else
            LocationManagementController.changeLocationName(id, name);
    }

    function deleteLocation(id) {
        statusMode = FluStatusLayoutType.Loading;
        LocationManagementController.deleteLocation(id);
    }

    launchMode: FluPageType.SingleTask
    Component.onCompleted: {
        loadAllLocation();
    }

    Connections {
        function onLoadAllLocationSuccess() {
            statusMode = FluStatusLayoutType.Success;
        }

        target: LocationManagementController
    }

    Connections {
        function onLoadAllLocationError(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: LocationManagementController
    }

    Connections {
        function onDeleteTLocationSuccess() {
            showSuccess("删除地点成功");
            loadAllLocation();
        }

        target: LocationManagementController
    }

    Connections {
        function onDeleteLocationError(message) {
            statusMode = FluStatusLayoutType.Success;
            showError("删除失败(错误信息: " + message + ")");
        }

        target: LocationManagementController
    }

    Connections {
        function onChangeLocationNameSuccess() {
            showSuccess("更改地点成功");
            loadAllLocation();
        }

        target: LocationManagementController
    }

    Connections {
        function onChangeLocationNameError(message) {
            statusMode = FluStatusLayoutType.Success;
            showError("更改失败(错误信息: " + message + ")");
        }

        target: LocationManagementController
    }

    Connections {
        function onAddLocationSuccess() {
            showSuccess("添加地点成功");
            loadAllLocation();
        }

        target: LocationManagementController
    }

    Connections {
        function onAddLocationError(message) {
            statusMode = FluStatusLayoutType.Success;
            showError("添加失败(错误信息: " + message + ")");
        }

        target: LocationManagementController
    }

    FluFrame {
        id: locationArea

        width: locationPage.width - locationPage.rightPadding - locationPage.leftPadding
        height: locationPage.height - locationPage.topPadding - locationPage.bottomPadding
        color: Qt.rgba(0, 0, 0, 0)

        FluFrame {
            id: editArea

            color: Qt.rgba(0, 0, 0, 0)
            height: editLocationTextBox.height + editLocationTextBox.anchors.topMargin
            width: editLocationTextBox.width + editLocationTextBox.anchors.leftMargin + operationBox.width + operationBox.anchors.leftMargin

            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 5
            }

            FluTextBox {
                id: editLocationTextBox

                text: forceItemName
                disabled: true
                width: locationTreeArea.width - operationBox.width - anchors.leftMargin
                height: 30

                anchors {
                    left: parent.left
                    leftMargin: 2
                    top: parent.top
                    topMargin: 2
                }

            }

            Rectangle {
                id: operationBox

                color: Qt.rgba(0, 0, 0, 0)
                visible: forceItemName != "" && editLocationId === -1
                width: editButton.width + editButton.anchors.leftMargin + deleteButton.width + deleteButton.anchors.leftMargin
                height: editButton.height + editButton.anchors.topMargin

                anchors {
                    left: editLocationTextBox.right
                    leftMargin: 5
                    top: parent.top
                    topMargin: 2
                }

                FluIconButton {
                    id: editButton

                    iconSource: FluentIcons.Edit
                    onClicked: {
                        editOperationBox.visible = true;
                        editLocationTextBox.disabled = false;
                        editLocationId = forceItemId;
                    }

                    anchors {
                        left: operationBox.left
                        leftMargin: 2
                        top: parent.top
                    }

                }

                FluIconButton {
                    id: deleteButton

                    iconSource: FluentIcons.Delete
                    onClicked: {
                        delete_btn_dialog.open();
                    }

                    anchors {
                        left: editButton.right
                        leftMargin: 1
                        top: parent.top
                    }

                }

            }

            Rectangle {
                id: editOperationBox

                function closeEditOperation() {
                    editOperationBox.visible = false;
                    editLocationTextBox.disabled = true;
                    forceItemName = "";
                    forceItemId = -1;
                    editLocationId = -1;
                    isNewLocation = false;
                    selectParentId = -1;
                    selectParentName = "";
                    editLocationTextBox.text = Qt.binding(function() {
                        return forceItemName;
                    });
                }

                color: Qt.rgba(0, 0, 0, 0)
                visible: editLocationId != -1
                width: submitButton.width + submitButton.anchors.leftMargin + cancelButton.width + cancelButton.anchors.leftMargin
                height: submitButton.height + submitButton.anchors.topMargin

                anchors {
                    left: editLocationTextBox.right
                    leftMargin: 5
                    top: parent.top
                    topMargin: 2
                }

                FluIconButton {
                    id: submitButton

                    iconSource: FluentIcons.Accept
                    onClicked: {
                        if (selectTree.visible) {
                            showError("父节点编辑中，请先完成操作");
                            return ;
                        }
                        if (isNewLocation) {
                            if (editLocationTextBox.text === "" || selectParentId === -1) {
                                showError("地点名或父节点不能为空！");
                                return ;
                            }
                        } else {
                            if (editLocationTextBox.text === "") {
                                showError("地点名不能为空！");
                                return ;
                            }
                        }
                        locationPage.submitLoactionChange(editLocationId, editLocationTextBox.text, selectParentId, isNewLocation);
                        editOperationBox.closeEditOperation();
                    }

                    anchors {
                        left: editOperationBox.left
                        leftMargin: 2
                        top: parent.top
                    }

                }

                FluIconButton {
                    id: cancelButton

                    iconSource: FluentIcons.Cancel
                    onClicked: {
                        if (selectTree.visible) {
                            showError("父节点编辑中，请先完成操作");
                            return ;
                        }
                        editOperationBox.closeEditOperation();
                    }

                    anchors {
                        left: submitButton.right
                        leftMargin: 1
                        top: parent.top
                    }

                }

            }

        }

        FluFrame {
            id: locationTreeArea

            border.width: 1
            border.color: "black"
            color: Qt.rgba(0, 0, 0, 0)
            width: (locationArea.width - anchors.leftMargin - border.width * 2) / 3
            height: locationArea.height - anchors.topMargin - editArea.height - editArea.anchors.topMargin - (border.width * 2)
            radius: 5

            anchors {
                top: editArea.bottom
                topMargin: 5
                left: parent.left
                leftMargin: 5
            }

            FluTreeView {
                id: locationTree

                selectionMode: FluTreeViewType.Single
                width: locationTreeArea.width - locationTreeArea.border.width * 2 - anchors.leftMargin
                height: locationTreeArea.height - anchors.topMargin - locationTreeArea.border.width * 2 - addLocationButton.height - addLocationButton.anchors.topMargin
                onItemClicked: (item) => {
                    forceItemName = item.data.name;
                    forceItemId = item.data.id;
                }

                anchors {
                    top: parent.top
                    topMargin: 5
                    left: parent.left
                    leftMargin: 5
                }

                Connections {
                    function onListReady() {
                        locationTree.updateData(locationListData);
                    }

                    target: locationPage
                }

            }

            FluIconButton {
                id: addLocationButton

                iconSource: FluentIcons.Add
                height: 46
                onClicked: {
                    if (editLocationId != -1) {
                        showError("有地点信息仍在编辑中！");
                        return ;
                    }
                    isNewLocation = true;
                    editLocationId = 0;
                    forceItemName = "";
                    editOperationBox.visible = true;
                    editLocationTextBox.disabled = false;
                }

                anchors {
                    top: locationTree.bottom
                    topMargin: 3
                    left: parent.left
                    leftMargin: 5
                }

            }

            MouseArea {
                id: locationTreeMouseArea

                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                visible: editLocationId != -1
                onClicked: {
                    if (isNewLocation)
                        showError("有新地点仍在编辑中！");
                    else
                        showError("有地点信息仍在编辑中！");
                }
            }

        }

        FluFrame {
            id: newLocationParentSelectBox

            visible: isNewLocation
            color: Qt.rgba(0, 0, 0, 0)
            height: locationArea.height - anchors.topMargin
            width: (locationArea.width - anchors.leftMargin) / 3

            anchors {
                top: parent.top
                topMargin: 10
                left: locationTreeArea.right
                leftMargin: 70
            }

            FluTextBox {
                id: parentNameText

                text: selectParentName
                width: newLocationParentSelectBox.width - selectButton.width - anchors.leftMargin
                height: 30
                disabled: true

                anchors {
                    left: parent.left
                    top: parent.top
                    topMargin: 2
                }

            }

            FluIconButton {
                id: selectButton

                iconSource: FluentIcons.MultiSelect
                onClicked: {
                    if (selectTree.visible) {
                        showError("父节点未编辑结束");
                        return ;
                    }
                    locationPage.changeParent();
                }

                anchors {
                    left: parentNameText.right
                    leftMargin: 2
                    top: parent.top
                    topMargin: 2
                }

            }

            FluFrame {
                border.width: 1
                border.color: "black"
                color: Qt.rgba(1, 1, 1, 0.4)
                width: newLocationParentSelectBox.width - anchors.leftMargin - border.width * 2
                height: newLocationParentSelectBox.height - parentNameText.height - parentNameText.anchors.topMargin - anchors.topMargin - border.width * 2
                radius: 5

                anchors {
                    left: parent.left
                    top: parentNameText.bottom
                    topMargin: 5
                }

                FluTreeView {
                    id: selectTree

                    selectionMode: FluTreeViewType.Single
                    visible: false
                    anchors.fill: parent
                    onItemClicked: (item) => {
                        selectParentName = item.data.name;
                        selectParentId = item.data.id;
                        selectTree.visible = false;
                    }

                    Connections {
                        function onChangeParent() {
                            selectTree.updateData(locationSelectData);
                            selectTree.visible = true;
                        }

                        target: locationPage
                    }

                }

                FluText {
                    id: toolTip

                    text: "请点击父节点编辑按钮"
                    fontSizeMode: Text.Fit
                    color: Qt.rgba(128 / 255, 128 / 255, 128 / 255, 0.8)
                    visible: !(selectTree.visible || (width < contentWidth && !selectTree.visible))
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }

        }

    }

    FluContentDialog {
        // 取消删除操作

        id: delete_btn_dialog

        title: "删除地点"
        message: "是否确定删除该地点？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        onNegativeClicked: {
        }
        positiveText: "确定"
        onPositiveClicked: {
            deleteLocation(forceItemId);
            editOperationBox.closeEditOperation();
        }
    }

}
