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

private:
    QString m_permissionId;
    QString m_event;
    QVector<QString> m_methodAllowed;
};

#endif // PERMISSIONENTRY_H
