import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/ui/global"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_feedback
    Layout.fillWidth: true

    Column {
        width: parent.width
        spacing: 15

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

                    FluRectangle {
                        id: item_img
                        height: 40
                        width: 40
                        radius: [20, 20, 20, 20]
                        anchors {
                            left: parent.left
                            top: parent.top
                            margins: 10
                        }
                        FluImage {
                            anchors.fill: parent
                            source: modelData.img
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
                        wrapMode: Text.WordWrap
                        width: parent.width - 30
                        font: FluTextStyle.Body
                        anchors {
                            top: item_img.bottom
                            topMargin: 5
                            left: parent.left
                            leftMargin: 10
                        }
                    }

                    FluIconButton {
                        iconSource: FluentIcons.Copy
                        anchors {
                            right: parent.right
                            bottom: parent.bottom
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
            id: listView
            width: parent.width
            implicitHeight: contentHeight
            interactive: false
            delegate: com_item

            Component.onCompleted: {
                model = loadData(1, 8)
            }
        }

        FluPagination {
            id: gagination
            anchors {
                left: parent.left
            }
            width: parent.width
            pageCurrent: 1
            itemCount: 28
            pageButtonCount: 7
            __itemPerPage: 8
            onRequestPage: (page, count) => {
                               listView.model = loadData(page, count)
                           }
        }
    }

    function loadData(page, count) {
        const dataSource = []
        for (var i = 0; i < count; i++) {
            if (page === 2) {
                dataSource.push({
                                    "img": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                                    "name": "amin",
                                    "comment": "C++ 是一种高级语言，它是由 Bjarne Stroustrup 于 1979 年在贝尔实验室开始设计开发的。C++ 进一步扩充和完善了 C 语言，是一种面向对象的程序设计语言。C++ 可运行于多种平台上，如 Windows、MAC 操作系统以及 UNIX 的各种版本。
本教程通过通俗易懂的语言来讲解 C++ 编程语言。"
                                })
            } else
                dataSource.push({
                                    "img": "qrc:/SAST_Evento/res/image/banner_3.jpg",
                                    "name": "admin",
                                    "comment": "C++ 是一种高级语言，它是由 Bjarne Stroustrup 于 1979 年在贝尔实验室开始设计开发的。C++ 进一步扩充和完善了 C 语言，是一种面向对象的程序设计语言。C++ 可运行于多种平台上，如 Windows、MAC 操作系统以及 UNIX 的各种版本。
本教程通过通俗易懂的语言来讲解 C++ 编程语言。"
                                })
        }
        return dataSource
    }
}
