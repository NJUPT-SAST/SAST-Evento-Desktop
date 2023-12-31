#ifndef SETTINGSHELPER_H
#define SETTINGSHELPER_H

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QScopedPointer>
#include <QSettings>
#include <QtCore/qobject.h>
#include <QtQml>

class SettingsHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(SettingsHelper)
    QML_SINGLETON
private:
    explicit SettingsHelper(QObject* parent = nullptr);

public:
    static SettingsHelper* getInstance();
    static SettingsHelper* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    ~SettingsHelper() override;
    void init(char* argv[]);
    Q_INVOKABLE void saveRender(const QString& render) {
        save("render", render);
    }
    Q_INVOKABLE QString getRender() {
        return get("render").toString();
    }

private:
    void save(const QString& key, QVariant val);
    QVariant get(const QString& key);

private:
    QScopedPointer<QSettings> m_settings;
};

#endif // SETTINGSHELPER_H
