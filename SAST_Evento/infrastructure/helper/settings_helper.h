#pragma once

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

class SettingsHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(SettingsHelper)
    QML_SINGLETON
private:
    explicit SettingsHelper(QObject* parent = nullptr);
    static SettingsHelper* m_instance;
public:
    static SettingsHelper* getInstance();
    static SettingsHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    ~SettingsHelper() override;

    Q_INVOKABLE void saveToken(const QString& token){
        save("token",token);
    }

    Q_INVOKABLE QString getToken(){
        return get("token").toString();
    }

private:
    void save(const QString& key,QVariant val);

    QVariant get(const QString& key);

private:
    QScopedPointer<QSettings> m_settings;
};
