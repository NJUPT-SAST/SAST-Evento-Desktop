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
        property int darkMode
        property bool nativeTextSet
        property bool enableAnimationSet
        property int colorIndex
        property string langMode
    }

    Component.onCompleted: {
        FluApp.init(app)
        FluTheme.darkMode = settings.value("darkMode", FluThemeType.System)
        FluTheme.enableAnimation = settings.value("enableAnimationSet", true)
        FluTheme.nativeText = settings.value("nativeTextSet", false)
        var list = [FluColors.Yellow, FluColors.Orange, FluColors.Red, FluColors.Magenta, FluColors.Purple, FluColors.Blue, FluColors.Teal, FluColors.Green]
        FluTheme.primaryColor = list[settings.value("colorIndex", 5)]
        appInfo.changeLang(settings.value("langMode", "Zh"))
        FluApp.routes = {
            "/": "qrc:/SAST_Evento/qml/window/MainWindow.qml",
            "/login": "qrc:/SAST_Evento/qml/window/LoginWindow.qml"
        }
        FluApp.initialRoute = "/"
        FluApp.run()
    }

    Connections {
        target: FluTheme
        function onDarkModeChanged() {
            settings.darkMode = FluTheme.darkMode
        }
    }
}
