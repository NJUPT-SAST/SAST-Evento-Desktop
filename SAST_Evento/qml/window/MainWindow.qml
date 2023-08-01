import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Qt.labs.platform
import QtCore
import FluentUI
import SAST_Evento

import "qrc:///SAST_Evento/qml/component"
import "qrc:///SAST_Evento/qml/global"
import "qrc:///SAST_Evento/qml/page"

CustomWindow {

    id: window
    title: "SAST Evento"
    width: 1000
    height: 640
    closeDestory: false
    minimumWidth: 520
    minimumHeight: 200
    appBarVisible: false
    launchMode: FluWindowType.SingleTask

    property var loginPageRegister: registerForWindowResult("/login")

    Settings {
        id: settings
        property string username
    }

    Component.onCompleted: {
        FluTools.setQuitOnLastWindowClosed(false)
        loginPageRegister.launch({
                                     "username": settings.value("username", "")
                                 })
    }

    Connections {
        target: loginPageRegister
        function onResult(data) {
            if (data.ok) {
                appInfo.changeIdentity(data.username, data.password)
                settings.username = data.username
            } else {
                showInfo("未登录，前往“我的”以登录账号")
            }
        }
    }

    Connections {
        target: appInfo
        function onLogin() {
            if (appInfo.identity.authority === 0)
                showInfo("未登录，前往“我的”以登录账号")
            else
                showSuccess("登录成功")
        }
    }

    closeFunc: function (event) {
        dialog_close.open()
        event.accepted = false
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/SAST_Evento/res/image/favicon.ico"
        tooltip: "SAST Evento"
        menu: Menu {
            MenuItem {
                text: "退出"
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
        title: "退出"
        message: "确定要退出程序吗？"
        negativeText: "最小化"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            window.hide()
            system_tray.showMessage("友情提示", "FluentUI已隐藏至托盘,点击托盘可再次激活窗口")
        }
        positiveText: "退出"
        neutralText: "取消"
        onPositiveClicked: {
            window.deleteWindow()
            FluApp.closeApp()
        }
    }

    Flipable {
        id: flipable
        anchors.fill: parent
        property bool flipped: false
        property real flipAngle: 0
        transform: Rotation {
            id: rotation
            origin.x: flipable.width / 2
            origin.y: flipable.height / 2
            axis {
                x: 0
                y: 1
                z: 0
            }
            angle: flipable.flipAngle
        }
        states: State {
            PropertyChanges {
                target: flipable
                flipAngle: 180
            }
            when: flipable.flipped
        }
        transitions: Transition {
            NumberAnimation {
                target: flipable
                property: "flipAngle"
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }
        back: Item {
            anchors.fill: flipable
            visible: flipable.flipAngle !== 0
            FluAppBar {
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                darkText: lang.dark_mode
                showDark: true
                z: 7
                darkClickListener: button => handleDarkChanged(button)
            }
            Row {
                z: 8
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: FluTools.isMacos() ? 20 : 5
                    leftMargin: 5
                }
                FluIconButton {
                    iconSource: FluentIcons.ChromeBack
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        flipable.flipped = false
                    }
                }
                FluIconButton {
                    iconSource: FluentIcons.Sync
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        loader.reload()
                    }
                }
            }
        }
        front: Item {
            id: page_front
            visible: flipable.flipAngle !== 180
            anchors.fill: flipable
            FluAppBar {
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                darkText: lang.dark_mode
                showDark: true
                darkClickListener: button => handleDarkChanged(button)
                z: 7
            }
            FluNavigationView {
                property int clickCount: 0
                id: nav_view
                width: parent.width
                height: parent.height
                z: 999
                //Stack模式，每次切换都会将页面压入栈中，随着栈的页面增多，消耗的内存也越多，内存消耗多就会卡顿，这时候就需要按返回将页面pop掉，释放内存。该模式可以配合FluPage中的launchMode属性，设置页面的启动模式
                //                 pageMode: FluNavigationView.Stack
                //NoStack模式，每次切换都会销毁之前的页面然后创建一个新的页面，只需消耗少量内存（推荐）
                //pageMode: FluNavigationView.NoStack
                // items: ItemsOriginal.item
                footerItems: ItemsFooter
                topPadding: FluTools.isMacos() ? 20 : 5
                displayMode: MainEvent.displayMode
                logo: "qrc:/SAST_Evento/res/image/favicon.ico"
                title: "SAST Evento"
                autoSuggestBox: FluAutoSuggestBox {
                    width: 280
                    anchors.centerIn: parent
                    iconSource: FluentIcons.Search
                    placeholderText: lang.search
                    onItemClicked: data => {
                                       ItemsOriginal.startPageByItem(data)
                                   }
                }

                Component.onCompleted: {
                    ItemsFooter.navigationView = nav_view
                }

                Connections {
                    target: ItemsOriginal
                    function onSourceChanged() {
                        nav_view.pageMode = FluNavigationViewType.Stack
                        ItemsOriginal.item.navigationView = nav_view
                        nav_view.items = ItemsOriginal.item
                        nav_view.setCurrentIndex(0)
                    }
                }
            }
        }
    }

    Component {
        id: com_reveal
        CircularReveal {
            id: reveal
            target: window.contentItem
            anchors.fill: parent
            onAnimationFinished: {
                //动画结束后释放资源
                loader_reveal.sourceComponent = undefined
            }
            onImageChanged: {
                changeDark()
            }
        }
    }

    Loader {
        id: loader_reveal
        anchors.fill: parent
    }

    function distance(x1, y1, x2, y2) {
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
    }
    function handleDarkChanged(button) {
        if (FluTools.isMacos() || !FluTheme.enableAnimation) {
            changeDark()
        } else {
            loader_reveal.sourceComponent = com_reveal
            var target = window.contentItem
            var pos = button.mapToItem(target, 0, 0)
            var mouseX = pos.x
            var mouseY = pos.y
            var radius = Math.max(distance(mouseX, mouseY, 0,
                                           0), distance(mouseX, mouseY,
                                                        target.width, 0),
                                  distance(mouseX, mouseY, 0,
                                           target.height), distance(
                                      mouseX, mouseY,
                                      target.width, target.height))
            var reveal = loader_reveal.item
            reveal.start(reveal.width * Screen.devicePixelRatio,
                         reveal.height * Screen.devicePixelRatio,
                         Qt.point(mouseX, mouseY), radius)
        }
    }

    function changeDark() {
        if (FluTheme.dark) {
            FluTheme.darkMode = FluThemeType.Light
        } else {
            FluTheme.darkMode = FluThemeType.Dark
        }
    }
}
