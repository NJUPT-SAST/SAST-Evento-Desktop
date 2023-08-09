#ifndef PERMISSIONENTRY_H
#define PERMISSIONENTRY_H

#include <QStringList>

struct PermissionEntry
{
    int id;
    int eventId;
    QStringList methodAllowed;
};

#endif // PERMISSIONENTRY_H
