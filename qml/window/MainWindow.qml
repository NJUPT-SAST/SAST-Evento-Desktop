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
    width: 1110
    height: 640
    closeDestory: false
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
        window.requestActivate()
        window.autoShow = true
        FluTools.setQuitOnLastWindowClosed(false)
        checkUpdate()
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/app.ico"
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
            system_tray.showMessage(lang.lang_hint, lang.lang_hint_info)
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
            id: item_departmentevents
            title: lang.lang_department_evento
            icon: FluentIcons.GroupList
            onTap: {
                nav_view.push("qrc:/qml/page/T_DepartmentEvents.qml")
            }
        }

        function createUserItems() {
            var adminItems = Qt.createQmlObject('import FluentUI;FluPaneItem {
id: item_schedule
count: 9
title: lang.lang_schedule
icon: FluentIcons.CheckList
onTap: {
nav_view.push("qrc:/qml/page/T_Schedule.qml")}}', items_original)
            children.push(adminItems)
        }

        function createAdminItems() {
            var adminItems1 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
title: lang.lang_calendar
icon: FluentIcons.Calendar
onTap: {
nav_view.push("qrc:/qml/page/T_Calendar.qml")}}', items_original)
            var adminItems2 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
title: lang.lang_user_feedback
icon: FluentIcons.Comment
onTap: {
nav_view.push("qrc:/qml/page/T_Feedback.qml")}}', items_original)
            children.push(adminItems1)
            children.push(adminItems2)
        }

        Component.onCompleted: {
            if (UserHelper.permission !== 1)
                createUserItems()
            if (UserHelper.permission === 3)
                createAdminItems()
        }
    }

    FluObject {
        id: items_footer
        FluPaneItemSeparator {}

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

        function createItems() {
            var adminItems = Qt.createQmlObject('import FluentUI;FluPaneItem {
title: lang.lang_my
icon: FluentIcons.Contact
onTap: {
nav_view.push("qrc:/qml/page/T_My.qml")}}', items_footer)
            children.push(adminItems)
        }

        Component.onCompleted: {
            if (UserHelper.permission !== 1)
                createItems()
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

    property alias displayMode: nav_view.displayMode

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
        logo: "qrc:/app.ico"
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
        location: FluTools.getApplicationDirPath() + "/config.ini"
        property var displayMode
        property alias x: window.x
        property alias y: window.y
        property alias windowWidth: window.width
        property alias windowHeight: window.height
    }

    FluContentDialog {
        property string newVersion
        property string body
        id: dialog_update
        title: "更新提示"
        message: "SAST Evento目前最新版本 " + newVersion + "\n当前应用版本 "
                 + appInfo.version + " \n现在是否去下载新版本？\n\n更新内容：\n" + body
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: lang.lang_cancel
        positiveText: lang.lang_ok
        onPositiveClicked: {
            Qt.openUrlExternally(
                        "https://github.com/NJUPT-SAST-Cpp/SAST-Evento-Desktop/releases/latest")
        }
    }

    function checkUpdate() {
        CheckUpdate.check()
    }

    Connections {
        target: CheckUpdate
        function onCheckSuccessEvent(version, description) {
            if (version !== appInfo.version) {
                dialog_update.newVersion = version
                dialog_update.body = description
                dialog_update.open()
            }
        }
    }

    Connections {
        target: CheckUpdate
        function onCheckErrorEvent(message) {
            showError(lang.lang_check_up_failure + message, 4000)
        }
    }
}
