#include <QFileInfo>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSettings>
#include <QStandardPaths>

#include "helper/settings_helper.h"
#include "lang/AppInfo.h"

int main(int argc, char* argv[]) {
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    QGuiApplication::setOrganizationName("NJUPT-SAST-C++");
    QGuiApplication::setOrganizationDomain("https://github.com/NJUPT-SAST-Cpp");
    QGuiApplication::setApplicationName("SAST Evento Desktop");

    SettingsHelper::getInstance()->init(argv);
    if (SettingsHelper::getInstance()->getRender() == "software") {
        QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    }

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(QStringLiteral(":/app.ico")));
    auto fontId = QFontDatabase::addApplicationFont(":/res/font/MiSans-Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.empty())
        QGuiApplication::setFont(QFont(fontFamilies[0]));

    auto* appInfo = new AppInfo();
    QQmlApplicationEngine engine;
    appInfo->init(&engine);

    const QUrl url(QStringLiteral("qrc:/qml/App.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    engine.load(url);
    const int exec = QGuiApplication::exec();
    if (exec == 931) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    return exec;
}
