import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

Window {
    id: app
    flags: Qt.SplashScreen
    Component.onCompleted: {
        FluApp.init(app)
        FluTheme.darkMode = FluDarkMode.System
        FluTheme.enableAnimation = true
        FluApp.routes = {
            "/":"qrc:/SAST_Evento/qml/window/MainWindow.qml",
            "/about":"qrc:/SAST_Evento/qml/window/AboutWindow.qml",
            "/login":"qrc:/SAST_Evento/qml/window/LoginWindow.qml",
            "/singleTaskWindow":"qrc:/SAST_Evento/qml/window/SingleTaskWindow.qml",
            "/standardWindow":"qrc:/SAST_Evento/qml/window/StandardWindow.qml",
            "/singleInstanceWindow":"qrc:/SAST_Evento/qml/window/SingleInstanceWindow.qml"
        }
        FluApp.initialRoute = "/"
        FluApp.run()
    }
}
