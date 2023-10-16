#include <FramelessHelper/Core/private/framelessconfig_p.h>
#include <FramelessHelper/Quick/framelessquickmodule.h>

#include <QFontDatabase>
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
    QGuiApplication::setWindowIcon(QIcon(QStringLiteral(":/app.ico")));
    auto fontId = QFontDatabase::addApplicationFont(":/res/font/MiSans-Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.empty())
        QGuiApplication::setFont(QFont(fontFamilies[0]));
    FramelessConfig::instance()->set(Global::Option::DisableLazyInitializationForMicaMaterial);
    FramelessConfig::instance()->set(Global::Option::CenterWindowBeforeShow);
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur);
    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
#ifdef Q_OS_WIN
    FramelessConfig::instance()->set(Global::Option::ForceHideWindowFrameBorder);
#endif
#ifdef Q_OS_MACOS
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur, false);
#endif
    auto* appInfo = new AppInfo();
    QQmlApplicationEngine engine;
    FramelessHelper::Quick::registerTypes(&engine);
#ifdef FLUENTUI_BUILD_STATIC_LIB
    engine.addImportPath("qrc:/");
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