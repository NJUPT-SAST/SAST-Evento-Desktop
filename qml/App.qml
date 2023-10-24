import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import FluentUI

Window {
    id: app
    flags: Qt.SplashScreen

    Settings {
        id: settings
        location: FluTools.getApplicationDirPath() + "/config.ini"
        property int darkMode
        property int nativeTextSet
        property int enableAnimationSet
        property int colorIndex
        property string langMode
        property int displayMode
    }

    Component.onCompleted: {
        FluApp.init(app)
        var list = [FluColors.Yellow, FluColors.Orange, FluColors.Red, FluColors.Magenta, FluColors.Purple, FluColors.Blue, FluColors.Teal, FluColors.Green]
        FluTheme.darkMode = settings.value("darkMode", FluThemeType.System)
        settings.darkMode = FluTheme.darkMode
        FluTheme.primaryColor = list[settings.value("colorIndex", 5)]
        settings.colorIndex = list.indexOf(FluTheme.primaryColor)
        FluTheme.enableAnimation = settings.value("enableAnimationSet", 1)
        FluTheme.nativeText = settings.value("nativeTextSet", 0)
        settings.displayMode = settings.value("displayMode",
                                              FluNavigationViewType.Auto)
        appInfo.changeLang(settings.value("langMode", "En"))
        FluApp.routes = {
            "/": "qrc:/qml/window/MainWindow.qml",
            "/login": "qrc:/qml/window/LoginWindow.qml",
            "/block": "qrc:/qml/window/EventoBlockWindow.qml"
        }
        FluApp.initialRoute = "/login"
        FluApp.run()
    }

    Connections {
        target: FluTheme
        function onDarkModeChanged() {
            settings.darkMode = FluTheme.darkMode
        }
    }

    Connections {
        target: FluTheme
        function onEnableAnimationChanged() {
            settings.enableAnimationSet = FluTheme.enableAnimation
        }
    }

    Connections {
        target: FluTheme
        function onNativeTextChanged() {
            settings.nativeTextSet = FluTheme.nativeText
        }
    }
}
