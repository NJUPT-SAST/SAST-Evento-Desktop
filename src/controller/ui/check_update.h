#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H

#include <QtQml>

class CheckUpdate : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(CheckUpdate)
    QML_SINGLETON

public:
    Q_INVOKABLE void check();

signals:
    void checkSuccessEvent(QString version, QString description);
    void checkErrorEvent(QString message);

private:
    CheckUpdate() = default;

public:
    static CheckUpdate* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
};

#endif // CHECKUPDATE_H
