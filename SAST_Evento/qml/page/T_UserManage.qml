import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/global"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_usermanage
    Layout.fillWidth: true

    Column {
        width: parent.width
        spacing: 15

        Component {
            id: com_item
            Item {
                Layout.topMargin: 10
                width: parent.width
                height: 80
                FluArea {
                    radius: 8
                    width: parent.width
                    height: 70
                    anchors.centerIn: parent

                    FluText {
                        id: item_id
                        text: modelData.id
                        font: FluTextStyle.Title
                        anchors {
                            left: parent.left
                            top: parent.top
                            leftMargin: 10
                            topMargin: 5
                        }
                    }

                    FluText {
                        id: item_comment
                        text: "权限 " + modelData.permission
                        wrapMode: Text.WordWrap
                        width: parent.width - 20
                        font: FluTextStyle.Body
                        anchors {
                            top: item_id.bottom
                            topMargin: 5
                            left: parent.left
                            leftMargin: 10
                        }
                    }

                    FluIconButton {
                        iconSource: FluentIcons.Edit
                        anchors {
                            right: item_comment.right
                            bottom: parent.bottom
                            bottomMargin: 5
                        }
                        onClicked: {

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
                model = loadData(1, 10)
            }
        }

        FluPagination {
            id: gagination
            anchors {
                left: parent.left
            }
            width: parent.width
            pageCurrent: 1
            itemCount: 40
            pageButtonCount: 7
            __itemPerPage: 10
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
                                    "id": "B12345678",
                                    "permission": 1
                                })
            } else
                dataSource.push({
                                    "id": "B12345666",
                                    "permission": 2
                                })
        }
        return dataSource
    }
}
