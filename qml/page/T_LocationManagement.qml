import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    id: locationPage
    launchMode: FluPageType.SingleTask
    // title: "Location Management"

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
        var res = []

        if (Array.isArray(data)) {
            for(var i = 0; i < data.length; i++) {
                var item = data[i]
                var children = []
                var isLeaf = false

                if(item.children && Array.isArray(item.children))
                    children = parseJSON(item.children)
                else
                    isLeaf = true
                res.push(locationTree.createItem(item.name, isLeaf, children, {
                                                     "id": item.id,
                                                     "name": item.name
                                                 }))
            }
        }
        else {
            res.push(locationTree.createItem(item.name, true, [], {
                         "id": data.id,
                         "name": data.name
                     }))
        }
        return res
    }

    function loadLocationInfo(locationJson) {
        locationListData = parseJSON(locationJson)
        locationSelectData.push(locationTree.createItem("\\", false, locationListData, {
                                                          "id": 0,
                                                          "name": "\\"
                                                      }))
        listReady()
    }

    function loadAllLocation() {
        statusMode = FluStatusViewType.Loading
        locationSelectData = []
        locationListData = []
        loadLocationInfo(JSON.parse(LocationManagementController.loadAllLocation()))
    }

    function submitLoactionChange(id, name, parentId, isAdd) {
        statusMode = FluStatusViewType.Loading
        if(isAdd) {
            LocationManagementController.addLocation(name, parentId)
        }
        else {
            LocationManagementController.changeLocationName(id, name)
        }
    }

    function deleteLocation(id) {
        statusMode = FluStatusViewType.Loading
        LocationManagementController.deleteLocation(id)
    }

    Connections {
        target: LocationManagementController
        function onLoadAllLocationSuccess() {
            statusMode = FluStatusViewType.Success
        }
    }

    Connections {
        target: LocationManagementController
        function onLoadAllLocationError(message) {
            errorText = message
            statusMode = FluStatusViewType.Error
        }
    }

    Connections {
        target: LocationManagementController
        function onDeleteTLocationSuccess() {
            showSuccess("删除地点成功")
            loadAllLocation()
        }
    }

    Connections {
        target: LocationManagementController
        function onDeleteLocationError(message) {
            statusMode = FluStatusViewType.Success
            showError("删除失败(错误信息: " + message + ")")
        }
    }

    Connections {
        target: LocationManagementController
        function onChangeLocationNameSuccess() {
            showSuccess("更改地点成功")
            loadAllLocation()
        }
    }

    Connections {
        target: LocationManagementController
        function onChangeLocationNameError(message) {
            statusMode = FluStatusViewType.Success
            showError("更改失败(错误信息: " + message + ")")
        }
    }

    Connections {
        target: LocationManagementController
        function onAddLocationSuccess() {
            showSuccess("添加地点成功")
            loadAllLocation()
        }
    }

    Connections {
        target: LocationManagementController
        function onAddLocationError(message) {
            statusMode = FluStatusViewType.Success
            showError("添加失败(错误信息: " + message + ")")
        }
    }

    Component.onCompleted: {
        loadAllLocation()
    }

    FluArea {
        id: locationArea
        width: locationPage.width -
               locationPage.rightPadding -
               locationPage.leftPadding
        height: locationPage.height -
                locationPage.topPadding -
                locationPage.bottomPadding
        color: Qt.rgba(0, 0, 0, 0)

        FluArea {
            id: editArea
            color: Qt.rgba(0, 0, 0, 0)
            height: editLocationTextBox.height +
                    editLocationTextBox.anchors.topMargin
            width: editLocationTextBox.width +
                   editLocationTextBox.anchors.leftMargin +
                   operationBox.width +
                   operationBox.anchors.leftMargin
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
                anchors {
                    left: parent.left
                    leftMargin: 2
                    top: parent.top
                    topMargin: 2
                }
                width: locationTreeArea.width -
                       operationBox.width -
                       anchors.leftMargin
                height: 30
            }

            Rectangle {
                id: operationBox
                color: Qt.rgba(0,0,0,0)
                visible: forceItemName != "" && editLocationId === -1
                anchors {
                    left: editLocationTextBox.right
                    leftMargin: 5
                    top: parent.top
                    topMargin: 2
                }
                width: editButton.width +
                       editButton.anchors.leftMargin +
                       deleteButton.width +
                       deleteButton.anchors.leftMargin
                height: editButton.height +
                        editButton.anchors.topMargin

                FluIconButton {
                    id: editButton
                    iconSource: FluentIcons.Edit
                    anchors {
                        left: operationBox.left
                        leftMargin: 2
                        top: parent.top
                    }

                    onClicked: {
                        editOperationBox.visible = true
                        editLocationTextBox.disabled = false
                        editLocationId = forceItemId
                    }
                }

                FluIconButton {
                    id: deleteButton
                    iconSource: FluentIcons.Delete
                    anchors {
                        left: editButton.right
                        leftMargin: 1
                        top: parent.top
                    }

                    onClicked: {
                        delete_btn_dialog.open()
                    }
                }
            }

            Rectangle {
                id: editOperationBox
                color: Qt.rgba(0, 0, 0, 0)
                visible: editLocationId != -1
                anchors {
                    left: editLocationTextBox.right
                    leftMargin: 5
                    top: parent.top
                    topMargin: 2
                }
                width: submitButton.width +
                       submitButton.anchors.leftMargin +
                       cancelButton.width +
                       cancelButton.anchors.leftMargin
                height: submitButton.height +
                        submitButton.anchors.topMargin

                function closeEditOperation() {
                    editOperationBox.visible = false
                    editLocationTextBox.disabled = true

                    forceItemName = ""
                    forceItemId = -1

                    editLocationId = -1
                    isNewLocation = false

                    selectParentId = -1
                    selectParentName = ""

                    editLocationTextBox.text = Qt.binding(function(){return forceItemName})
                }

                FluIconButton {
                    id: submitButton
                    iconSource: FluentIcons.Accept
                    anchors {
                        left: editOperationBox.left
                        leftMargin: 2
                        top: parent.top
                    }

                    onClicked: {
                        if(selectTree.visible) {
                            showError("父节点编辑中，请先完成操作")
                            return
                        }
                        if(isNewLocation) {
                            if(editLocationTextBox.text === "" || selectParentId === -1) {
                                showError("地点名或父节点不能为空！")
                                return
                            }
                        }
                        else {
                            if(editLocationTextBox.text === "") {
                                showError("地点名不能为空！")
                                return
                            }
                        }

                        locationPage.submitLoactionChange(editLocationId,
                                                          editLocationTextBox.text,
                                                          selectParentId,
                                                          isNewLocation)
                        editOperationBox.closeEditOperation()
                    }
                }

                FluIconButton {
                    id: cancelButton
                    iconSource: FluentIcons.Cancel
                    anchors {
                        left: submitButton.right
                        leftMargin: 1
                        top: parent.top
                    }

                    onClicked: {
                        if(selectTree.visible) {
                            showError("父节点编辑中，请先完成操作")
                            return
                        }
                        editOperationBox.closeEditOperation()
                    }
                }
            }
        }

        FluArea {
            id: locationTreeArea
            border.width: 1
            border.color: "black"
            color: Qt.rgba(0,0,0,0)
            width: (locationArea.width -
                   anchors.leftMargin -
                   border.width * 2) / 3
            height: locationArea.height -
                    anchors.topMargin -
                    editArea.height -
                    editArea.anchors.topMargin -
                    (border.width * 2)

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
                width: locationTreeArea.width -
                       locationTreeArea.border.width * 2 -
                       anchors.leftMargin
                height: locationTreeArea.height -
                        anchors.topMargin -
                        locationTreeArea.border.width * 2 -
                        addLocationButton.height -
                        addLocationButton.anchors.topMargin
                anchors {
                    top: parent.top
                    topMargin: 5
                    left: parent.left
                    leftMargin: 5
                }

                Connections {
                    target: locationPage
                    function onListReady() {
                        locationTree.updateData(locationListData)
                    }
                }

                onItemClicked: item => {
                                   forceItemName = item.data.name
                                   forceItemId = item.data.id
                }
            }

            FluIconButton {
                id: addLocationButton
                iconSource: FluentIcons.Add
                height: 46
                anchors {
                    top: locationTree.bottom
                    topMargin: 3
                    left: parent.left
                    leftMargin: 5
                }

                onClicked: {
                    if(editLocationId != -1) {
                        showError("有地点信息仍在编辑中！")
                        return
                    }
                    isNewLocation = true
                    editLocationId = 0
                    forceItemName = ""
                    editOperationBox.visible = true
                    editLocationTextBox.disabled = false
                }
            }

            MouseArea {
                id: locationTreeMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                visible: editLocationId != -1
                onClicked: {
                    if(isNewLocation) {
                        showError("有新地点仍在编辑中！")
                    }
                    else {
                        showError("有地点信息仍在编辑中！")
                    }
                }
            }
        }

        FluArea {
            id: newLocationParentSelectBox
            visible: isNewLocation
            color: Qt.rgba(0, 0, 0, 0)
            anchors {
                top: parent.top
                topMargin: 10
                left: locationTreeArea.right
                leftMargin: 70
            }
            height: locationArea.height -
                    anchors.topMargin
            width: (locationArea.width -
                    anchors.leftMargin) / 3

            FluTextBox {
                id: parentNameText
                text: selectParentName
                width: newLocationParentSelectBox.width -
                       selectButton.width-
                       anchors.leftMargin
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

                anchors {
                    left: parentNameText.right
                    leftMargin: 2
                    top: parent.top
                    topMargin: 2
                }

                onClicked: {
                    if(selectTree.visible) {
                        showError("父节点未编辑结束")
                        return
                    }
                    locationPage.changeParent()
                }
            }

            FluArea {
                border.width: 1
                border.color: "black"
                color: Qt.rgba(1,1,1,0.4)
                width: newLocationParentSelectBox.width -
                       anchors.leftMargin -
                       border.width * 2
                height: newLocationParentSelectBox.height -
                        parentNameText.height -
                        parentNameText.anchors.topMargin -
                        anchors.topMargin -
                        border.width * 2
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
                    Connections {
                        target: locationPage
                        function onChangeParent() {
                            selectTree.updateData(locationSelectData)
                            selectTree.visible = true
                        }
                    }

                    onItemClicked: item => {
                                       selectParentName = item.data.name
                                       selectParentId = item.data.id
                                       selectTree.visible = false
                                   }
                }

                FluText {
                    id: toolTip
                    text: "请点击父节点编辑按钮"
                    fontSizeMode: Text.Fit
                    color: Qt.rgba(128/255,128/255,128/255,0.8)
                    visible: !(selectTree.visible || (width < contentWidth && !selectTree.visible))
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    FluContentDialog{
        id:delete_btn_dialog
        title:"删除地点"
        message:"是否确定删除该地点？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText:"取消"
        onNegativeClicked:{
            // 取消删除操作
        }
        positiveText:"确定"
        onPositiveClicked:{
            deleteLocation(forceItemId)
            editOperationBox.closeEditOperation()
        }
    }
}
