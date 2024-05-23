import FluentUI
import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FluLauncher {
    id: app

    Component.onCompleted: {
        FluApp.init(app);
        var list = [FluColors.Yellow, FluColors.Orange, FluColors.Red, FluColors.Magenta, FluColors.Purple, FluColors.Blue, FluColors.Teal, FluColors.Green];
        FluTheme.darkMode = settings.value("darkMode", FluThemeType.System);
        settings.darkMode = FluTheme.darkMode;
        FluTheme.accentColor = list[settings.value("colorIndex", 5)] || FluColors.Blue;
        settings.colorIndex = list.indexOf(FluTheme.accentColor);
        FluTheme.animationEnabled = settings.value("enableAnimationSet", 1);
        FluTheme.nativeText = settings.value("nativeTextSet", 1);
        settings.displayMode = settings.value("displayMode", FluNavigationViewType.Auto);
        appInfo.changeLang(settings.value("langMode", "En"));
        FluRouter.routes = {
            "/": "qrc:/qml/window/MainWindow.qml",
            "/login": "qrc:/qml/window/LoginWindow.qml",
            "/block": "qrc:/qml/window/EventoBlockWindow.qml"
        };
        FluRouter.navigate("/login");
    }

    Settings {
        id: settings

        property int darkMode
        property int nativeTextSet
        property int enableAnimationSet
        property int colorIndex
        property string langMode
        property int displayMode

        location: FluTools.getApplicationDirPath() + "/config.ini"
    }

    Connections {
        function onDarkModeChanged() {
            settings.darkMode = FluTheme.darkMode;
        }

        target: FluTheme
    }

    Connections {
        function onAnimationEnabledChanged() {
            settings.enableAnimationSet = FluTheme.animationEnabled;
        }

        target: FluTheme
    }

    Connections {
        function onNativeTextChanged() {
            settings.nativeTextSet = FluTheme.nativeText;
        }

        target: FluTheme
    }

}
