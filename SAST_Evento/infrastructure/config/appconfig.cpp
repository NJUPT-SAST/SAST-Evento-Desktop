#include "AppConfig.h"

Q_GLOBAL_STATIC(AppConfig, appConfig)

AppConfig* AppConfig::instance() { return appConfig; }

AppConfig::AppConfig(QObject* parent) : QObject{parent} {
    appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

QString AppConfig::getLogDir() { return existsDir(appDir + "/logs"); }

QString AppConfig::getApplicationDir() {
    return QCoreApplication::applicationDirPath();
}

QString AppConfig::getHtmlDir() { return getApplicationDir() + "/html"; }

QString AppConfig::getDatabseDir() { return existsDir(appDir + "/db"); }

QString AppConfig::getConfigDir() { return existsDir(appDir + "/config"); }

QString AppConfig::getImageCacheDir() {
    return existsDir(appDir + "/cache/image");
}

QString AppConfig::getJsonClassDir() {
    return existsDir(appDir + "/temp/JsonClass");
}

QString AppConfig::existsDir(const QString& path) {
    QDir dir = path;
    if (!dir.exists(path)) dir.mkpath(path);
    return path;
}
