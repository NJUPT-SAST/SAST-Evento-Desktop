import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Qt.labs.platform
import QtCore
import FluentUI
import SAST_Evento
import "../imports"

CustomWindow {
    id: window
    width: 1100
    height: 640
    closeDestory: true
    minimumWidth: 520
    minimumHeight: 200
    appBarVisible: false
    autoShow: false
    launchMode: FluWindowType.SingleTask
    title: "SAST Evento"

    closeFunc: function (event) {
        dialog_close.open()
        event.accepted = false
    }

    Component.onCompleted: {
        //        if (!UserHelper.isLogin()) {
        //            window.autoShow = false
        //            FluApp.navigate("/login")
        //        } else {
        window.autoShow = true
        FluTools.setQuitOnLastWindowClosed(false)
        //}
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/res/image/favicon.ico"
        tooltip: "SAST Evento"
        menu: Menu {
            MenuItem {
                text: lang.lang_exit
                onTriggered: {
                    window.deleteWindow()
                    FluApp.closeApp()
                }
            }
        }
        onActivated: reason => {
                         if (reason === SystemTrayIcon.Trigger) {
                             window.show()
                             window.raise()
                             window.requestActivate()
                         }
                     }
    }

    FluContentDialog {
        id: dialog_close
        title: lang.lang_exit
        message: lang.lang_determine_exit
        negativeText: lang.lang_minimalSideBar
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            window.hide()
            system_tray.showMessage("提示", "SAST Evento已隐藏至托盘，点击托盘可再次激活窗口")
        }
        positiveText: lang.lang_exit
        neutralText: lang.lang_cancel
        onPositiveClicked: {
            window.deleteWindow()
            FluApp.closeApp()
        }
    }

    FluObject {
        id: items_original
        FluPaneItem {
            id: item_home
            title: lang.lang_plaza
            icon: FluentIcons.Home
            onTap: {
                nav_view.push("qrc:/qml/page/T_Plaza.qml")
            }
        }

        FluPaneItem {
            id: item_schedule
            count: 9
            title: lang.lang_schedule
            icon: FluentIcons.Calendar
            onTap: {
                nav_view.push("qrc:/qml/page/T_Schedule.qml")
            }
        }

        FluPaneItemExpander {
            title: lang.lang_manage
            icon: FluentIcons.AllApps
            FluPaneItem {
                title: lang.lang_timesheet
                onTap: {
                    nav_view.push("qrc:/qml/page/T_Timesheet.qml")
                }
            }
            FluPaneItem {
                title: lang.lang_feedback
                onTap: {
                    nav_view.push("qrc:/qml/page/T_Feedback.qml")
                }
            }
        }

        FluPaneItemExpander {
            title: lang.lang_others
            icon: FluentIcons.ViewAll
            FluPaneItem {
                title: lang.lang_user_manage
                onTap: {
                    nav_view.push("qrc:/qml/page/T_UserManage.qml")
                }
            }
            FluPaneItem {
                title: lang.lang_upload_souvenir_card
                onTap: {
                    nav_view.push("qrc:/page/T_SouvenirCard.qml")
                }
            }
            FluPaneItem {
                title: lang.lang_slide
                onTap: {
                    nav_view.push("qrc:/qml/page/T_Slide.qml")
                }
            }
        }
    }

    FluObject {
        id: items_footer
        FluPaneItemSeparator {}
        FluPaneItem {
            title: lang.lang_my
            icon: FluentIcons.Contact
            onTap: {
                nav_view.push("qrc:/qml/page/T_My.qml")
            }
        }

        FluPaneItem {
            title: lang.lang_theming
            icon: FluentIcons.Brightness
            onTap: {
                nav_view.push("qrc:/qml/page/T_Theme.qml")
            }
        }

        FluPaneItem {
            title: lang.lang_settings
            icon: FluentIcons.Settings
            onTap: {
                nav_view.push("qrc:/qml/page/T_Settings.qml")
            }
        }
    }

    FluAppBar {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        darkText: lang.lang_dark_mode
        showDark: true
        z: 7
    }

    FluIconButton {

        anchors {
            top: parent.top
            left: parent.left
            topMargin: FluTools.isMacos() ? 20 : 10
            leftMargin: 155
        }

        iconSource: FluentIcons.Sync
        width: 30
        height: 30
        iconSize: 13
        onClicked: {

            // TODO
        }
    }

    FluNavigationView {
        id: nav_view
        width: parent.width
        height: parent.height
        z: 999
        navWidth: 200
        items: items_original
        footerItems: items_footer
        topPadding: FluTools.isMacos() ? 20 : 5
        displayMode: settings.displayMode
        logo: "qrc:/res/favicon.ico"
        title: "SAST Evento"
        Component.onCompleted: {
            setCurrentIndex(0)
        }
    }

    function pushPage(item) {
        nav_view.push(item)
    }

    Settings {
        id: settings
        property var displayMode
    }
}
