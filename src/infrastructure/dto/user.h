#ifndef DTO_USER_H
#define DTO_USER_H

#include "types.h"

struct DTO_User {
    QString avatar;
    QString biography;
    QString email;
    UserID id;
    QString linkId;
    QStringList link;
    QString nickname;
    QString organization;
    QString studentId;
};

#endif // DTO_USER_H
