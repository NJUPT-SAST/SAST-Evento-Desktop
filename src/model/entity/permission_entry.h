#ifndef PERMISSION_ENTRY_H
#define PERMISSION_ENTRY_H

#include <QStringList>

struct PermissionEntry {
    int id;
    int eventId;
    QStringList methodAllowed;
};

#endif // PERMISSION_ENTRY_H
