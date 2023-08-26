#ifndef PERMISSIONHELPER_H
#define PERMISSIONHELPER_H

#include <QtQml>
#include <QObject>

class PermissionHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PermissionHelper)
    QML_SINGLETON

    Q_PROPERTY(QString permissionJson MEMBER m_permissionJson NOTIFY permissionJsonChanged)

public:
    static PermissionHelper *getInstance();

    static PermissionHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updatePermission(const QString &m_permissionJson);

private:
    QString m_permissionJson;
    bool m_isEdited; // true: 编辑模式 false: 创建模式

signals:
    void permissionJsonChanged();

};

#endif // PERMISSIONHELPER_H
