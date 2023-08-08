#include "settings_helper.h"

#include "infrastructure/config/appconfig.h"

SettingsHelper* SettingsHelper::m_instance = nullptr;

SettingsHelper *SettingsHelper::getInstance()
{
    if(SettingsHelper::m_instance == nullptr){
        SettingsHelper::m_instance = new SettingsHelper;
    }
    return SettingsHelper::m_instance;
}

SettingsHelper::SettingsHelper(QObject *parent) : QObject(parent)
{
    const QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    const QString iniFileName = fileInfo.completeBaseName() + ".ini";
    const QString iniFilePath = AppConfig::instance()->getConfigDir() + QDir::separator() + iniFileName;
    m_settings.reset(new QSettings(iniFilePath, QSettings::IniFormat));
}

SettingsHelper::~SettingsHelper() = default;

void SettingsHelper::save(const QString& key,QVariant val)
{
    QByteArray data = {};
    QDataStream stream(&data, QDataStream::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_6);
    stream << val;
    m_settings->setValue(key, data);
}

QVariant SettingsHelper::get(const QString& key){
    const QByteArray data = m_settings->value(key).toByteArray();
    if (data.isEmpty()) {
        return {};
    }
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_5_6);
    QVariant val;
    stream >> val;
    return val;
}
