import QtQuick
import QtQuick.Layouts
import FluentUI
import org.wangwenx190.FramelessHelper
import SAST_Evento

FluWindow {
    id: window
    property bool fixSize
    property alias titleVisible: title_bar.titleVisible
    property alias showClose: title_bar.showClose
    property alias showMinimize: title_bar.showMinimize
    property alias showMaximize: title_bar.showMaximize
    property bool appBarVisible: true
    property bool autoShow: true
    default property alias content: container.data
    FluAppBar {
        id: title_bar
        title: window.title
        visible: window.appBarVisible
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        darkText: lang.lang_dark_mode
    }
    Item {
        id: container
        anchors {
            top: title_bar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        clip: true
    }
    FramelessHelper {
        id: framless_helper
        onReady: {
            setTitleBarItem(title_bar)
            moveWindowToDesktopCenter()
            setHitTestVisible(title_bar.minimizeButton())
            setHitTestVisible(title_bar.maximizeButton())
            setHitTestVisible(title_bar.closeButton())
            setWindowFixedSize(fixSize)
            title_bar.maximizeButton.visible = !fixSize
            if (blurBehindWindowEnabled)
                window.background = undefined
            if (window.autoShow) {
                window.show()
            }
        }
    }
    Connections {
        target: FluTheme
        function onDarkChanged() {
            if (FluTheme.dark)
                FramelessUtils.systemTheme = FramelessHelperConstants.Dark
            else
                FramelessUtils.systemTheme = FramelessHelperConstants.Light
        }
    }

    Component.onCompleted: {
        FramelessUtils.systemTheme
                = FluTheme.dark ? FramelessHelperConstants.Dark : FramelessHelperConstants.Light
    }

    function setHitTestVisible(com) {
        framless_helper.setHitTestVisible(com)
    }
    function setTitleBarItem(com) {
        framless_helper.setTitleBarItem(com)
    }
}
