import "../component"
import "../window"
import FluentUI
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluScrollableStatusPage {
    id: typePage

    property int deleteTypeId: -1
    property string typeListJson_str: ""
    property var typeListJson
    property int newIndex: -1
    property int freshIndex: -1

    signal cancelNewType()

    function loadModel() {
        for (var i = 0; i < typeListJson.length; i++) {
            typeListModel.append(typeListJson[i]);
        }
    }

    function loadAllType() {
        statusMode = FluStatusLayoutType.Loading;
        typeListJson = JSON.parse(TypeManagementController.loadAllType());
        typeListModel.clear();
        loadModel();
    }

    function deleteType() {
        statusMode = FluStatusLayoutType.Loading;
        TypeManagementController.deleteType(deleteTypeId);
    }

    function freshList() {
        loadAllType();
        newIndex = -1;
        freshIndex = -1;
    }

    launchMode: FluPageType.SingleTask
    title: "Type Management"
    Component.onCompleted: {
        loadAllType();
        cancelNewType.connect(freshList);
    }

    Connections {
        function onLoadAllTypeSuccess() {
            statusMode = FluStatusLayoutType.Success;
        }

        target: TypeManagementController
    }

    Connections {
        function onLoadAllTypeError(message) {
            errorText = message;
            statusMode = FluStatusLayoutType.Error;
        }

        target: TypeManagementController
    }

    Connections {
        function onDeleteTypeSuccess() {
            loadAllType();
            showSuccess("删除类型成功");
        }

        target: TypeManagementController
    }

    Connections {
        function onDeleteTypeError(message) {
            statusMode = FluStatusLayoutType.Success;
            showError("删除失败(错误信息: " + message + ")");
        }

        target: TypeManagementController
    }

    Connections {
        function onChangeTypeNameSuccess() {
            freshList();
            showSuccess("更改成功");
        }

        target: TypeManagementController
    }

    Connections {
        function onChangeTypeNameError(message) {
            freshList();
            showError("更改失败(错误信息: " + message + ")");
        }

        target: TypeManagementController
    }

    Connections {
        function onAddTypeSuccess() {
            freshList();
            showSuccess("添加成功");
        }

        target: TypeManagementController
    }

    Connections {
        function onAddTypeError(message) {
            freshList();
            showError("添加失败(错误信息: " + message + ")");
        }

        target: TypeManagementController
    }

    Component {
        id: com_item

        Item {
            id: rootItem

            Layout.topMargin: 10
            width: listView.width
            height: 90

            FluFrame {
                radius: 8
                width: parent.width
                height: 80
                anchors.centerIn: parent

                Rectangle {
                    anchors.fill: parent
                    radius: 8
                    width: parent.width
                    color: Qt.rgba(0, 0, 0, 0)

                    FluText {
                        id: com_name

                        opacity: newIndex === index ? 0 : 1
                        text: model.name
                        font: FluTextStyle.Title

                        anchors {
                            left: parent.left
                            leftMargin: 15
                            verticalCenter: parent.verticalCenter
                        }

                    }

                    Rectangle {
                        id: editBox

                        visible: newIndex === index

                        anchors {
                            left: parent.left
                            leftMargin: 15
                            verticalCenter: parent.verticalCenter
                        }

                        FluTextBox {
                            id: name_edit

                            text: model.name
                            font: FluTextStyle.Body

                            anchors {
                                left: parent.left
                                verticalCenter: parent.verticalCenter
                            }

                        }

                        FluIconButton {
                            id: editSubButton

                            iconSource: FluentIcons.Accept
                            onClicked: {
                                if (name_edit.text === "") {
                                    showInfo("类型名不能为空");
                                    return ;
                                }
                                typeLoadText.visible = true;
                                editBox.visible = false;
                                com_name.opacity = 1;
                                if (newIndex === index)
                                    TypeManagementController.addType(name_edit.text);
                                else
                                    TypeManagementController.changeTypeName(model.id, name_edit.text);
                            }

                            anchors {
                                left: name_edit.right
                                leftMargin: 10
                                verticalCenter: parent.verticalCenter
                            }

                        }

                        FluIconButton {
                            id: cancelSubButton

                            iconSource: FluentIcons.Cancel
                            onClicked: {
                                if (newIndex !== -1) {
                                    newIndex = -1;
                                    typeListModel.remove(index);
                                    return ;
                                }
                                com_name.opacity = 1;
                                deleteButton.visible = true;
                                editButton.visible = true;
                                editBox.visible = false;
                                name_edit.text = model.name;
                                freshIndex = -1;
                            }

                            anchors {
                                left: editSubButton.right
                                leftMargin: 5
                                verticalCenter: parent.verticalCenter
                            }

                        }

                    }

                    FluText {
                        id: typeLoadText

                        visible: false
                        font: FluTextStyle.Body
                        text: newIndex === index ? "添加类型中..." : "更改类型中..."

                        anchors {
                            left: com_name.right
                            leftMargin: 15
                            verticalCenter: parent.verticalCenter
                        }

                    }

                    FluIconButton {
                        id: deleteButton

                        visible: !(newIndex === index)
                        iconSource: FluentIcons.Delete
                        onClicked: {
                            deleteTypeId = model.id;
                            delete_btn_dialog.open();
                        }

                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: parent.right
                            rightMargin: 10
                        }

                    }

                    FluIconButton {
                        id: editButton

                        visible: !(newIndex === index)
                        iconSource: FluentIcons.Edit
                        onClicked: {
                            if (freshIndex != -1 || newIndex != -1) {
                                showError("有未编辑提交的类型名");
                                return ;
                            }
                            freshIndex = index;
                            com_name.opacity = 0;
                            deleteButton.visible = false;
                            editButton.visible = false;
                            editBox.visible = true;
                        }

                        anchors {
                            bottom: parent.bottom
                            bottomMargin: 10
                            right: deleteButton.left
                            rightMargin: 10
                        }

                    }

                }

            }

        }

    }

    FluIconButton {
        id: addButton

        iconSource: FluentIcons.Add
        Layout.alignment: Qt.AlignRight
        onClicked: {
            if (newIndex !== -1) {
                showError("有未保存的新类型");
                return ;
            }
            if (freshIndex != -1) {
                showError("有未编辑提交的类型名");
                return ;
            }
            newIndex = typeListJson.length;
            var jsonItem = JSON.parse("{\"name\": \"\",\"id\":" + newIndex + "}");
            typeListModel.append(jsonItem);
        }
    }

    ListView {
        id: listView

        model: typeListModel
        Layout.fillWidth: true
        implicitHeight: contentHeight
        interactive: false
        delegate: com_item
    }

    FluContentDialog {
        // 取消删除操作

        id: delete_btn_dialog

        title: "删除类型"
        message: "是否确定删除该类型？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        onNegativeClicked: {
        }
        positiveText: "确定"
        onPositiveClicked: {
            deleteType();
        }
    }

    ListModel {
        id: typeListModel

        objectName: "typeListModel"
    }

}
