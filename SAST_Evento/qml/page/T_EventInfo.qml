import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI
import "qrc:///SAST_Evento/qml/component"

FluScrollablePage {
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

        FluText {
            text: "活动组织部门"
            font: FluTextStyle.Subtitle
        }

        FluText {
            width: parent.width
            text: "活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息活动详细信息"
            font: FluTextStyle.Body
            wrapMode: Text.WordWrap
        }

        FluToggleButton {
            text: "参加活动"
            disabled: false
            width: 120
            onClicked: {
                if (checked) {
                    text = "已参加，点击取消"
                    showSuccess("参加成功")
                } else {
                    text = "参加活动"
                    showSuccess("取消成功")
                }
            }
        }
    }
}
