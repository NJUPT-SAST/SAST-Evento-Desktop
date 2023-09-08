#ifndef DTO_PERMISSION_H
#define DTO_PERMISSION_H

#include "types.h"

struct DTO_Permission
{
    int id;
    QStringList allMethodName;
    UserID userId;
    EventoID eventId;
    QDateTime gmtUpdate;
};

struct DTO_PermissionTreeItem {
    QString title;
    QString value;
	std::vector<DTO_PermissionTreeItem> children;
};

typedef std::vector<DTO_PermissionTreeItem> DTO_PermissionTree;

#endif // DTO_PERMISSION_H
