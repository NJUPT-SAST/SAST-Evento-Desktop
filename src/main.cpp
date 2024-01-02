#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QNetworkProxy>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    QGuiApplication::setOrganizationName("NJUPT-SAST-C++");
    QGuiApplication::setOrganizationDomain("https://github.com/NJUPT-SAST-Cpp");
    QGuiApplication::setApplicationName("SAST Evento Desktop");

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(QStringLiteral(":/app.ico")));
    auto fontId = QFontDatabase::addApplicationFont(":/res/font/MiSans-Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.empty())
        QGuiApplication::setFont(QFont(fontFamilies[0]));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/App.qml"));
    engine.load(url);
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);

    return app.exec();
}
