import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/global"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    Column {
        spacing: 15
        Layout.fillWidth: true
        Layout.topMargin: 10
        FluRectangle {
            radius: [8, 8, 8, 8]
            width: parent.width
            height: 300
            FluImage {
                anchors.fill: parent
                source: "https://gitee.com/zhu-zichu/zhu-zichu/raw/74f075efe2f8d3c3bb7ba3c2259e403450e4050b/image/banner_1.jpg"
                fillMode: Image.PreserveAspectCrop
                onStatusChanged: {
                    if (status === Image.Error) {
                        showError("图片加载失败，请重新加载")
                    }
                }
                clickErrorListener: function () {
                    source = "https://gitee.com/zhu-zichu/zhu-zichu/raw/74f075efe2f8d3c3bb7ba3c2259e403450e4050b/image/banner_1.jpg"
                }
            }
        }

        FluText {
            text: "活动标题"
            font: FluTextStyle.TitleLarge
        }

        FluTextButton {
            text: "活动组织部门"
            font: FluTextStyle.Subtitle

            onClicked: {
                ItemsOriginal.item.navigationView.push(
                            "qrc:/SAST_Evento/qml/page/T_DepartmentEvents.qml")
            }
        }

        FluText {
            width: parent.width
            text: "活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息"
            font: FluTextStyle.Body
            wrapMode: Text.WordWrap
        }

        FluToggleButton {
            id: btn_participate
            text: lang.lang_participate_in
            disabled: false
            width: 120
            onClicked: {
                if (checked) {
                    text = lang.lang_cancel
                    showSuccess("参加成功")
                    loader.item.publishDiasabled = false
                } else {
                    text = lang.lang_participate_in
                    showSuccess("取消成功")
                    loader.item.publishDiasabled = true
                }
            }
        }
    }

    Loader {
        id: loader
        sourceComponent: com_comment
        Layout.fillWidth: true
        Layout.topMargin: 30
    }

    Component {
        id: com_comment
        Column {
            property alias publishDiasabled: btn_publish.disabled
            width: parent.width
            spacing: 15
            FluText {
                text: lang.lang_comment
                font: FluTextStyle.Subtitle
            }

            FluMultilineTextBox {
                id: multiine_textbox
                placeholderText: "输入你的评价，Ctrl+Enter换行"
                width: parent.width
                Layout.topMargin: 10
            }

            FluFilledButton {
                id: btn_publish
                text: lang.lang_publish
                disabled: true
                anchors {
                    right: parent.right
                }
            }

            Component {
                id: com_item
                Item {
                    Layout.topMargin: 10
                    width: parent.width
                    height: 85 + item_comment.lineCount * 15
                    FluArea {
                        radius: 8
                        width: parent.width
                        height: 70 + item_comment.lineCount * 15
                        anchors.centerIn: parent
                        paddings: 10
                        color: "transparent"
                        Rectangle {
                            anchors.fill: parent
                            radius: 8
                            color: "transparent"
                        }
                        FluRectangle {
                            id: item_img
                            height: 40
                            width: 40
                            radius: [20, 20, 20, 20]
                            anchors {
                                left: parent.left
                            }
                            FluImage {
                                anchors.fill: parent
                                source: modelData.image
                                fillMode: Image.PreserveAspectCrop
                            }
                        }

                        FluText {
                            id: item_name
                            text: modelData.name
                            font: FluTextStyle.Title
                            anchors {
                                left: item_img.right
                                leftMargin: 10
                                top: item_img.top
                            }
                        }

                        FluText {
                            id: item_comment
                            text: modelData.comment
                            wrapMode: Text.WrapAnywhere
                            width: parent.width - 20
                            font: FluTextStyle.Body
                            anchors {
                                top: item_img.bottom
                                topMargin: 5
                            }
                        }

                        FluIconButton {
                            iconSource: FluentIcons.Copy
                            anchors {
                                left: item_comment.right
                                bottom: parent.bottom
                                rightMargin: 5
                                bottomMargin: 5
                            }
                            onClicked: {
                                FluTools.clipText(item_comment.text)
                                showSuccess("复制成功")
                            }
                        }
                    }
                }
            }

            ListView {
                width: parent.width
                implicitHeight: contentHeight
                interactive: false
                delegate: com_item

                Component.onCompleted: {
                    model = getEventItems()
                }
            }
        }
    }

    function getEventItems() {
        var arr = []
        for (var i = 0; i < 10; ++i) {
            arr.push({
                         "image": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                         "name": "admin",
                         "time": "2023.07.10 15:18",
                         "comment": "C++ 是一种高级语言，它是由 Bjarne Stroustrup 于 1979 年在贝尔实验室开始设计开发的。C++ 进一步扩充和完善了 C 语言，是一种面向对象的程序设计语言。C++ 可运行于多种平台上，如 Windows、MAC 操作系统以及 UNIX 的各种版本。
本教程通过通俗易懂的语言来讲解 C++ 编程语言。",
                         "id": i
                     })
        }
        return arr
    }
}
