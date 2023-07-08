#include <FramelessHelper/Core/private/framelessconfig_p.h>
#include <FramelessHelper/Quick/framelessquickmodule.h>

#include <QDir>
#include <QGuiApplication>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "AppInfo.h"
#include "src/component/CircularReveal.h"

FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[]) {
    // 将样式设置为Basic，不然会导致组件显示异常
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    FramelessHelper::Quick::initialize();
    QGuiApplication::setOrganizationName("SAST");
    QGuiApplication::setOrganizationDomain("https://www.github.com");
    QGuiApplication::setApplicationName("SAST_Evento");
    QGuiApplication app(argc, argv);
#ifdef Q_OS_WIN  // 此设置仅在Windows下生效
    FramelessConfig::instance()->set(
        Global::Option::ForceHideWindowFrameBorder);
#endif
    FramelessConfig::instance()->set(
        Global::Option::DisableLazyInitializationForMicaMaterial);
    FramelessConfig::instance()->set(Global::Option::CenterWindowBeforeShow);
    FramelessConfig::instance()->set(
        Global::Option::ForceNonNativeBackgroundBlur);
    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
#ifdef Q_OS_MACOS
    FramelessConfig::instance()->set(
        Global::Option::ForceNonNativeBackgroundBlur, false);
#endif
    AppInfo *appInfo = new AppInfo();
    IPC ipc(0);
    if (!appInfo->isOwnerProcess(&ipc)) {
        return 0;
    }
    app.setQuitOnLastWindowClosed(false);
    qmlRegisterType<CircularReveal>("SAST_Evento", 1, 0, "CircularReveal");
    QQmlApplicationEngine engine;
    FramelessHelper::Quick::registerTypes(&engine);
    appInfo->init(&engine);
    const QUrl url(QStringLiteral("qrc:///SAST_Evento/qml/App.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
