#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QObject>
#include <QtQml/qqml.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

class CommonHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CommonHelper)
    QML_SINGLETON
private:
    explicit CommonHelper(QObject* parent = nullptr);
    static CommonHelper* m_instance;
public:
    static CommonHelper* getInstance();
    static CommonHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    Q_INVOKABLE bool isJson(QString);
    Q_INVOKABLE QString toBase64(QString);
    Q_INVOKABLE QString fromBase64(QString);
    Q_INVOKABLE QString md5(QString);
    Q_INVOKABLE QString sha1(QString);
    Q_INVOKABLE QString sha224(QString);
    Q_INVOKABLE QString sha256(QString);
    Q_INVOKABLE QString sha384(QString);
    Q_INVOKABLE QString sha512(QString);
    Q_INVOKABLE qint64 currentTimeMillis();
    Q_INVOKABLE QString maxString(QString,int max);
    Q_INVOKABLE QJsonObject json2Object(QString);
    Q_INVOKABLE QString object2Json(QJsonObject);
    Q_INVOKABLE void jsonNonNull(QString);
    Q_INVOKABLE void restart();
};

#endif  // COMMONHELPER_H
