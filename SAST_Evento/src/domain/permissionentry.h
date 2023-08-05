#ifndef PERMISSIONENTRY_H
#define PERMISSIONENTRY_H


#include <QString>
#include <QVector>

class PermissionEntry
{
public:
    PermissionEntry(QString permissionId,
                    QString event,
                    QVector<QString> methodAllowed);
    QString getPermissionId() const { return m_permissionId; }
    QString getEvent() const { return m_event; }
    QVector<QString> getMethodAllowed() const { return m_methodAllowed; }

private:
    QString m_permissionId;
    QString m_event;
    QVector<QString> m_methodAllowed;
};

#endif // PERMISSIONENTRY_H
