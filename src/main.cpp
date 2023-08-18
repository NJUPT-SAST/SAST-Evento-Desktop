#include <FramelessHelper/Core/private/framelessconfig_p.h>
#include <FramelessHelper/Quick/framelessquickmodule.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "lang/AppInfo.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"
#include "latest_evento_model.h"
#include "user_brief_model.h"

FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[]) {
    qputenv("QT_QUICK_CONTROLS_STYLE","Basic");
    FramelessHelper::Quick::initialize();
    QGuiApplication::setOrganizationName("NJUPT-SAST-C++");
    QGuiApplication::setOrganizationDomain("https://github.com/NJUPT-SAST-Cpp");
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral("qrc:/res/favicon.ico")));
    FramelessConfig::instance()->set(Global::Option::DisableLazyInitializationForMicaMaterial);
    FramelessConfig::instance()->set(Global::Option::CenterWindowBeforeShow);
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur);
    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
#ifdef Q_OS_WIN // 此设置仅在Windows下生效
    FramelessConfig::instance()->set(Global::Option::ForceHideWindowFrameBorder);
#endif
#ifdef Q_OS_MACOS
    FramelessConfig::instance()->set(Global::Option::ForceNonNativeBackgroundBlur,false);
#endif
    AppInfo* appInfo = new AppInfo();
    QQmlApplicationEngine engine;
    FramelessHelper::Quick::registerTypes(&engine);
#ifdef FLUENTUI_BUILD_STATIC_LIB
    engine.addImportPath("qrc:/"); // 让静态资源可以被QML引擎搜索到
#endif
    appInfo->init(&engine);
    qmlRegisterSingletonInstance("MyModel", 1, 0, "SlideModel", SlideModel::getInstance());
    qmlRegisterSingletonInstance("MyModel", 1, 0, "UndertakingEventoModel", UndertakingEventoModel::getInstance());
    qmlRegisterSingletonInstance("MyModel", 1, 0, "LatestEventoModel", LatestEventoModel::getInstance());
    qmlRegisterSingletonInstance("MyModel", 1, 0, "UserBriefModel", UserBriefModel::getInstance());

    const QUrl url(QStringLiteral("qrc:/qml/App.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
