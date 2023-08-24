import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI

FluScrollablePage {
    launchMode: FluPageType.SingleTask

    function createOrg() {
        var subtrees = []
        var name = ["阿里巴巴", "腾讯", "百度", "京东", "华为", "小米", "字节跳动", "美团", "滴滴"]
        for (var i = 0; i < name.length; i++) {
            subtrees.push(tree_view.createItem(name[i], false))
        }
        return [tree_view.createItem("dep", true, subtrees)]
    }

    function gridHeight() {
        return (eventCard.model / 2 + 1) * eventCard.cellHeight
    }

    FluTextButton {
        text: lang.lang_subscribe
        checked: true
        Layout.alignment: Qt.AlignRight
        onClicked: {
            checked = !checked
            if (!checked) {
                text = lang.lang_unsubscribe
                showInfo("已订阅")
                textColor = disableColor
            } else {
                text = lang.lang_subscribe
                showInfo("已取消订阅")
                textColor = pressedColor
            }
        }
    }

    RowLayout {
        Layout.topMargin: 10
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 20

        FluArea{
            Layout.topMargin: 10
            Layout.fillHeight: true
            paddings: 10
            width: 250
            FluTreeView{
                id:tree_view
                width:240
                anchors{
                    top:parent.top
                    left:parent.left
                    bottom:parent.bottom
                }
                onItemClicked:
                    (model)=>{
                        showSuccess(model.text)
                    }

                Component.onCompleted: {
                    updateData(createOrg())
                }
            }
        }

        GridView {
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
            model: 10
        }

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
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    FluImage {
                        anchors.fill: parent
                        source: "qrc:/res/image/banner_3.png"
                        fillMode: Image.PreserveAspectCrop
                    }
                }

                FluText {
                    id: item_title
                    text: model.title
                    font: FluTextStyle.Subtitle
                    anchors {
                        left: item_icon.right
                        leftMargin: 12
                        top: item_icon.top
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
