import FluentUI
import Qt.labs.platform as P
import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Window
import SAST_Evento

FluWindow {
    id: window

    property alias displayMode: nav_view.displayMode

    function distance(x1, y1, x2, y2) {
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    function handleDarkChanged(button) {
        if (FluTools.isMacos() || !FluTheme.enableAnimation) {
            changeDark();
        } else {
            loader_reveal.sourceComponent = com_reveal;
            var target = window.contentItem;
            var pos = button.mapToItem(target, 0, 0);
            var mouseX = pos.x;
            var mouseY = pos.y;
            var radius = Math.max(distance(mouseX, mouseY, 0, 0), distance(mouseX, mouseY, target.width, 0), distance(mouseX, mouseY, 0, target.height), distance(mouseX, mouseY, target.width, target.height));
            var reveal = loader_reveal.item;
            reveal.start(reveal.width * Screen.devicePixelRatio, reveal.height * Screen.devicePixelRatio, Qt.point(mouseX, mouseY), radius);
        }
    }

    function changeDark() {
        if (FluTheme.dark)
            FluTheme.darkMode = FluThemeType.Light;
        else
            FluTheme.darkMode = FluThemeType.Dark;
    }

    function pushPage(item) {
        nav_view.push(item);
    }

    function checkUpdate() {
        CheckUpdate.check();
    }

    title: "SAST Evento"
    width: 1110
    height: 640
    closeDestory: false
    minimumWidth: 520
    minimumHeight: 200
    launchMode: FluWindowType.SingleTask
    appBar: undefined
    closeListener: function(event) {
        dialog_close.open();
        event.accepted = false;
    }
    Component.onCompleted: {
        FluTools.setQuitOnLastWindowClosed(false);
        checkUpdate();
    }

    P.SystemTrayIcon {
        id: system_tray

        visible: true
        icon.source: "qrc:/app.ico"
        tooltip: "SAST Evento"
        onActivated: (reason) => {
            if (reason === P.SystemTrayIcon.Trigger) {
                window.show();
                window.raise();
                window.requestActivate();
            }
        }

        menu: P.Menu {
            MenuItem {
                text: lang.lang_exit
                onTriggered: {
                    window.deleteWindow();
                    FluApp.closeApp();
                }
            }

        }

    }

    FluContentDialog {
        id: dialog_close

        title: lang.lang_exit
        message: lang.lang_determine_exit
        negativeText: lang.lang_minimalSideBar
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            window.hide();
            system_tray.showMessage(lang.lang_hint, lang.lang_hint_info);
        }
        positiveText: lang.lang_exit
        neutralText: lang.lang_cancel
        onPositiveClicked: {
            window.close();
            FluApp.exit();
        }
    }

    FluObject {
        id: items_original

        function createUserItems() {
            var userItems1 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
id: item_departmentevents
title: lang.lang_department_evento
icon: FluentIcons.GroupList
onTap: {
nav_view.push("qrc:/qml/page/T_DepartmentEvents.qml")}}', items_original);
            var userItems2 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
id: item_schedule
count: 9
title: lang.lang_schedule
icon: FluentIcons.CheckList
onTap: {
nav_view.push("qrc:/qml/page/T_Schedule.qml")}}', items_original);
            children.push(userItems1);
            children.push(userItems2);
        }

        function createAdminItems() {
            var adminItems1 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
title: lang.lang_user_feedback
icon: FluentIcons.Comment
onTap: {
nav_view.push("qrc:/qml/page/T_Feedback.qml")}}', items_original);
            children.push(adminItems1);
        }

        Component.onCompleted: {
            if (UserHelper.permission > UserHelper.GuestPermission)
                createUserItems();

            if (UserHelper.permission === UserHelper.AdminPermission)
                createAdminItems();

        }

        FluPaneItem {
            id: item_home

            title: lang.lang_plaza
            icon: FluentIcons.Home
            onTap: {
                nav_view.push("qrc:/qml/page/T_Plaza.qml");
            }
        }

        FluPaneItem {
            id: item_calendar

            title: lang.lang_calendar
            icon: FluentIcons.Calendar
            onTap: {
                nav_view.push("qrc:/qml/page/T_Calendar.qml");
            }
        }

    }

    FluObject {
        id: items_footer

        function createItems() {
            var items1 = Qt.createQmlObject('import FluentUI;
FluPaneItem {
title: lang.lang_my
icon: FluentIcons.Contact
onTap: {
nav_view.push("qrc:/qml/page/T_My.qml")}}', items_footer);
            children.push(items1);
        }

        Component.onCompleted: {
            if (UserHelper.permission > UserHelper.GuestPermission)
                createItems();

        }

        FluPaneItemSeparator {
        }

        FluPaneItem {
            title: lang.lang_theming
            icon: FluentIcons.Brightness
            onTap: {
                nav_view.push("qrc:/qml/page/T_Theme.qml");
            }
        }

        FluPaneItem {
            title: lang.lang_settings
            icon: FluentIcons.Settings
            onTap: {
                nav_view.push("qrc:/qml/page/T_Settings.qml");
            }
        }

    }

    FluAppBar {
        darkText: lang.lang_dark_mode
        showDark: true
        darkClickListener: (button) => {
            return handleDarkChanged(button);
        }
        z: 7

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

    }

    Component {
        id: com_reveal

        CircularReveal {
            id: reveal

            target: window.contentItem
            anchors.fill: parent
            onAnimationFinished: {
                loader_reveal.sourceComponent = undefined;
            }
            onImageChanged: {
                changeDark();
            }
        }

    }

    Loader {
        id: loader_reveal

        anchors.fill: parent
    }

    FluNavigationView {
        id: nav_view

        width: parent.width
        height: parent.height
        cellWidth: 200
        z: 999
        pageMode: FluNavigationViewType.Stack
        items: items_original
        footerItems: items_footer
        topPadding: FluTools.isMacos() ? 20 : 5
        displayMode: settings.displayMode
        logo: "qrc:/app.ico"
        title: "SAST Evento"
        Component.onCompleted: {
            setCurrentIndex(0);
        }
    }

    Settings {
        id: settings

        property var displayMode
        property alias x: window.x
        property alias y: window.y
        property alias windowWidth: window.width
        property alias windowHeight: window.height

        location: FluTools.getApplicationDirPath() + "/config.ini"
    }

    FluContentDialog {
        id: dialog_update

        property string newVersion
        property string body

        title: "更新提示"
        message: "SAST Evento目前最新版本 " + newVersion + "\n当前应用版本 " + appInfo.version + " \n现在是否去下载新版本？\n\n更新内容：\n" + body
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: lang.lang_cancel
        positiveText: lang.lang_ok
        onPositiveClicked: {
            Qt.openUrlExternally("https://github.com/NJUPT-SAST-Cpp/SAST-Evento-Desktop/releases/latest");
            FluApp.exit();
        }
    }

    Connections {
        function onCheckSuccessEvent(version, description) {
            if (version !== appInfo.version) {
                dialog_update.newVersion = version;
                dialog_update.body = description;
                dialog_update.open();
            }
        }

        target: CheckUpdate
    }

    Connections {
        function onCheckErrorEvent(message) {
            showError(lang.lang_check_up_failure + message, 4000);
        }

        target: CheckUpdate
    }

}
