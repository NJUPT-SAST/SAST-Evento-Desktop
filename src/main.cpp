#include <QApplication>
#include <QFileInfo>
#include <QFontDatabase>
#include <QIcon>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSettings>
#include <QStandardPaths>

#include "helper/settings_helper.h"
#include "lang/AppInfo.h"

int main(int argc, char* argv[]) {
    QApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    QApplication::setOrganizationName("NJUPT-SAST-C++");
    QApplication::setOrganizationDomain("https://github.com/NJUPT-SAST-Cpp");
    QApplication::setApplicationName("SAST Evento Desktop");

    SettingsHelper::getInstance()->init(argv);
    if (SettingsHelper::getInstance()->getRender() == "software") {
        QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    }

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/app.ico")));
    auto fontId = QFontDatabase::addApplicationFont(":/res/font/MiSans-Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.empty())
        QApplication::setFont(QFont(fontFamilies[0]));

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
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QApplication::quit);
    engine.load(url);
    const int exec = QApplication::exec();
    if (exec == 931) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    return exec;
}
