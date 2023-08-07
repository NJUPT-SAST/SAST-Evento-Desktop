#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QCoreApplication>
#include <QDir>
#include <QGlobalStatic>
#include <QObject>
#include <QStandardPaths>

class AppConfig : public QObject {
    Q_OBJECT

   public:
    static AppConfig* instance();
    explicit AppConfig(QObject* parent = nullptr);

    Q_INVOKABLE QString getLogDir();
    Q_INVOKABLE QString getImageCacheDir();
    Q_INVOKABLE QString getJsonClassDir();
    Q_INVOKABLE QString getDatabseDir();
    Q_INVOKABLE QString getConfigDir();
    Q_INVOKABLE QString getApplicationDir();
    Q_INVOKABLE QString getHtmlDir();

   private:
    QString existsDir(const QString& path);

   private:
    QString appDir;
};

#endif  // APPCONFIG_H
