import "../component"
import "../window"
import FluentUI
import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FluScrollableStatusPage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_theming

    Settings {
        id: settings

        property int colorIndex

        location: FluTools.getApplicationDirPath() + "/config.ini"
    }

    FluFrame {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 270
        padding: 10

        ColumnLayout {
            spacing: 0

            anchors {
                left: parent.left
            }

            RowLayout {
                Layout.topMargin: 10

                Repeater {
                    id: rep

                    model: [FluColors.Yellow, FluColors.Orange, FluColors.Red, FluColors.Magenta, FluColors.Purple, FluColors.Blue, FluColors.Teal, FluColors.Green]

                    delegate: FluRectangle {
                        width: 42
                        height: 42
                        radius: [4, 4, 4, 4]
                        color: mouse_item.containsMouse ? Qt.lighter(modelData.normal, 1.1) : modelData.normal

                        FluIcon {
                            anchors.centerIn: parent
                            iconSource: FluentIcons.AcceptMedium
                            iconSize: 15
                            visible: modelData === FluTheme.accentColor
                            color: FluTheme.dark ? Qt.rgba(0, 0, 0, 1) : Qt.rgba(1, 1, 1, 1)
                        }

                        MouseArea {
                            id: mouse_item

                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                FluTheme.accentColor = modelData;
                                settings.colorIndex = model.index;
                            }
                        }

                    }

                }

            }

            FluText {
                text: lang.lang_dark_mode
                Layout.topMargin: 20
            }

            FluToggleSwitch {
                Layout.topMargin: 5
                checked: FluTheme.dark
                onClicked: {
                    if (FluTheme.dark)
                        FluTheme.darkMode = FluThemeType.Light;
                    else
                        FluTheme.darkMode = FluThemeType.Dark;
                }
            }

            FluText {
                text: lang.lang_native_text_rendering
                Layout.topMargin: 20
            }

            FluToggleSwitch {
                Layout.topMargin: 5
                onClicked: {
                    FluTheme.nativeText = !FluTheme.nativeText;
                }
                Component.onCompleted: {
                    checked = FluTheme.nativeText;
                }
            }

            FluText {
                text: lang.lang_animation_effect
                Layout.topMargin: 20
            }

            FluToggleSwitch {
                Layout.topMargin: 5
                onClicked: {
                    FluTheme.animationEnabled = !FluTheme.animationEnabled;
                }
                Component.onCompleted: {
                    checked = FluTheme.animationEnabled;
                }
            }

        }

    }

}
