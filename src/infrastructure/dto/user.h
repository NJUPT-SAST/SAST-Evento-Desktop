#ifndef DTO_USER_H
#define DTO_USER_H

#include "permission.h"
#include "types.h"

struct DTO_User {
    UserID id;
    QString linkId;
    QString studentId;
    QString email;
    QString nickname;
    QString avatar;
    QString organization;
    QString biography;
    QString link;
};

#endif // DTO_USER_H