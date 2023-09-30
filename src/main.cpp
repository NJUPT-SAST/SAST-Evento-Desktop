#include <FramelessHelper/Core/private/framelessconfig_p.h>
#include <FramelessHelper/Quick/framelessquickmodule.h>

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

#include "lang/AppInfo.h"

FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char* argv[]) {
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    FramelessHelper::Quick::initialize();
    QGuiApplication::setOrganizationName("NJUPT-SAST-C++");
    QGuiApplication::setOrganizationDomain("https://github.com/NJUPT-SAST-Cpp");
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral("app.ico")));
    FramelessConfig::instance()->set(Global::Option::DisableLazyInitializationForMicaMaterial);
    FramelessConfig::instance()->set(Global::Option::CenterWindowBeforeShow);
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur);
    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
#ifdef Q_OS_WIN // 此设置仅在Windows下生效
    FramelessConfig::instance()->set(Global::Option::ForceHideWindowFrameBorder);
#endif
#ifdef Q_OS_MACOS
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur, false);
#endif
    AppInfo* appInfo = new AppInfo();
    QQmlApplicationEngine engine;
    FramelessHelper::Quick::registerTypes(&engine);
#ifdef FLUENTUI_BUILD_STATIC_LIB
    engine.addImportPath("qrc:/"); // 让静态资源可以被QML引擎搜索到
#endif
    appInfo->init(&engine);

    const QUrl url(QStringLiteral("qrc:/qml/App.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
