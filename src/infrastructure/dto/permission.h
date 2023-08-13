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

#endif // DTO_PERMISSION_H
