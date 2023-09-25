import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtCore
import FluentUI
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_settings

    Settings {
        id: settings
        property string langMode
        property int displayMode
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 128
        paddings: 10

        ColumnLayout {
            spacing: 5
            anchors {
                top: parent.top
                left: parent.left
            }
            FluText {
                text: lang.lang_dark_mode
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": lang.lang_followSystem,
                        "mode": FluThemeType.System
                    }, {
                        "title": lang.lang_light,
                        "mode": FluThemeType.Light
                    }, {
                        "title": lang.lang_dark,
                        "mode": FluThemeType.Dark
                    }]
                delegate: FluRadioButton {
                    checked: FluTheme.darkMode === modelData.mode
                    text: modelData.title
                    clickListener: function () {
                        FluTheme.darkMode = modelData.mode
                    }
                }
            }
        }
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 160
        paddings: 10

        ColumnLayout {
            spacing: 5
            anchors {
                top: parent.top
                left: parent.left
            }
            FluText {
                text: lang.lang_navigation_view_display_mode
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": lang.lang_openSideBar,
                        "mode": FluNavigationViewType.Open
                    }, {
                        "title": lang.lang_compactSideBar,
                        "mode": FluNavigationViewType.Compact
                    }, {
                        "title": lang.lang_minimalSideBar,
                        "mode": FluNavigationViewType.Minimal
                    }, {
                        "title": lang.lang_automatical,
                        "mode": FluNavigationViewType.Auto
                    }]
                delegate: FluRadioButton {
                    checked: settings.displayMode === modelData.mode
                    text: modelData.title
                    clickListener: function () {
                        settings.displayMode = modelData.mode
                        MainWindow.window.displayMode = modelData.mode
                    }
                }
            }
        }
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 80
        paddings: 10

        ColumnLayout {
            spacing: 10
            anchors {
                top: parent.top
                left: parent.left
            }

            FluText {
                text: lang.lang_locale
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }

            Flow {
                spacing: 5
                Repeater {
                    id: langSetting
                    model: ["Zh", "En"]
                    delegate: FluRadioButton {
                        checked: appInfo.lang.objectName === modelData
                        text: modelData === "En" ? lang.lang_en : lang.lang_zh
                        clickListener: function () {
                            settings.langMode = modelData
                            appInfo.changeLang(settings.langMode)
                        }
                    }
                }
            }
        }
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 80
        paddings: 10

        ColumnLayout {
            spacing: 10
            anchors {
                top: parent.top
                left: parent.left
            }

            FluText {
                text: lang.lang_locale
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }

            FluFilledButton {
                text: "检查更新"
                onClicked: {
                    checkUpdate()
                }
            }
        }
    }

    FluHttp {
        id: http
    }

    FluContentDialog {
        property string newVersion
        property string body
        id: dialog_update
        title: "更新提示"
        message: "SAST Evento目前最新版本 " + newVersion + " -- 当前应用版本 "
                 + appInfo.version + " \n现在是否去下载新版本？\n\n更新内容：\n" + body
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        positiveText: "确定"
        onPositiveClicked: {
            Qt.openUrlExternally("https://sast.fun")
        }
    }

    function checkUpdate() {
        var callable = {}
        callable.onStart = function () {
            console.debug("start check update...")
        }
        callable.onFinish = function () {
            console.debug("check update finish")
        }
        callable.onSuccess = function (result) {
            var data = JSON.parse(result)
            console.debug("current version " + appInfo.version)
            console.debug("new version " + data.tag_name)
            if (data.tag_name !== appInfo.version) {
                dialog_update.newVersion = data.tag_name
                dialog_update.body = data.body
                dialog_update.open()
            } else {
                showMessage("当前已是最新版本")
            }
        }
        callable.onError = function (status, errorString) {
            console.debug(status + ";" + errorString)
        }
        http.get("/*FIX ME: api*/", callable)
    }
}
