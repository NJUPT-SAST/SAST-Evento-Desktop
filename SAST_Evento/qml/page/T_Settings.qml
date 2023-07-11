import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/global"
import "qrc:///SAST_Evento/qml/component"

FluScrollablePage {

    title: lang.settings

    Settings {
        id: settings
        property var darkMode
        property int displayMode
        property string langMode
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
                text: lang.dark_mode
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": lang.followSystem,
                        "mode": FluDarkMode.System
                    }, {
                        "title": lang.light,
                        "mode": FluDarkMode.Light
                    }, {
                        "title": lang.dark,
                        "mode": FluDarkMode.Dark
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
                text: lang.navigation_view_display_mode
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": lang.openSideBar,
                        "mode": FluNavigationView.Open
                    }, {
                        "title": lang.compactSideBar,
                        "mode": FluNavigationView.Compact
                    }, {
                        "title": lang.minimalSideBar,
                        "mode": FluNavigationView.Minimal
                    }, {
                        "title": lang.automatical,
                        "mode": FluNavigationView.Auto
                    }]
                delegate: FluRadioButton {
                    checked: MainEvent.displayMode === modelData.mode
                    text: modelData.title
                    clickListener: function () {
                        settings.displayMode = modelData.mode
                        MainEvent.displayMode = settings.displayMode
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
                text: lang.locale
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
                        text: modelData === "En" ? lang.en : lang.zh
                        clickListener: function () {
                            settings.langMode = modelData
                            appInfo.changeLang(settings.langMode)
                        }
                    }
                }
            }
        }
    }
}
