import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtCore
import FluentUI
import SAST_Evento
import "../window"

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_settings

    Settings {
        id: settings
        location: FluTools.getApplicationDirPath() + "/config.ini"
        property string langMode
        property int displayMode
        property string render
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
                        "title": lang.lang_automatic,
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
        height: 95
        paddings: 10

        ColumnLayout {
            spacing: 5
            anchors {
                top: parent.top
                left: parent.left
            }

            FluText {
                text: lang.lang_check_update
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            FluText {
                text: lang.lang_current_version + appInfo.version
                font: FluTextStyle.Caption
            }

            Timer {
                id: timer_progress
                interval: 200
                onTriggered: {
                    btn_progress.progress = (btn_progress.progress + 0.1).toFixed(
                                0.8)
                    if (btn_progress.progress == 1) {
                        timer_progress.stop()
                    } else {
                        timer_progress.start()
                    }
                }
            }

            Connections {
                target: CheckUpdate
                function onCheckSuccessEvent(version, description) {
                    btn_progress.progress = 1
                    if (version === appInfo.version)
                        showInfo(lang.lang_is_currently_latest_version, 4000)
                }
            }

            Connections {
                target: CheckUpdate
                function onCheckErrorEvent(message) {
                    btn_progress.progress = 1
                }
            }

            FluProgressButton {
                id: btn_progress
                text: lang.lang_check_update
                onClicked: {
                    btn_progress.progress = 0
                    timer_progress.restart()
                    checkUpdate()
                }
            }
        }
    }

    function checkUpdate() {
        CheckUpdate.check()
    }

    FluArea{
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 60 + text_hint.implicitHeight
        paddings: 10
        FluCheckBox{
            id: checkbox_render
            text:"Software Render"
            checked: SettingsHelper.getRender() === "software"
            anchors.top: parent.top
            anchors.topMargin: 5
            onClicked: {
                if(SettingsHelper.getRender() === "software"){
                    SettingsHelper.saveRender("")
                }else{
                    SettingsHelper.saveRender("software")
                }
                dialog_restart.open()
            }
        }
        FluText {
            id: text_hint
            anchors {
                top: checkbox_render.bottom
                topMargin: 10
            }
            text: lang.lang_software_render_hint
            font: FluTextStyle.Caption
            width: parent.width
            wrapMode: Text.WordWrap
        }
    }

    FluContentDialog{
        id:dialog_restart
        title: lang.lang_hint
        message: lang.lang_restart_app_hint
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: lang.lang_cancel
        positiveText: lang.lang_ok
        onPositiveClicked:{
            FluApp.exit(931)
        }
    }

}
