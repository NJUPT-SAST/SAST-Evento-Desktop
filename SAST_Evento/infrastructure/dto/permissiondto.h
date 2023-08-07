#ifndef PERMISSIONDTO_H
#define PERMISSIONDTO_H

#include <QStringList>

struct PermissionDTO
{
    int id;
    QStringList allMethodName;
    QString userId;
    int eventId;
    QString gmtUpdate;
};

#endif // PERMISSIONDTO_H
