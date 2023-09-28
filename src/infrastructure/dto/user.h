#ifndef DTO_USER_H
#define DTO_USER_H

#include "permission.h"
#include "types.h"

struct DTO_User {
    UserID id;
    QString name;
    Image avatar;
    QString email;
    QString description;
    std::vector<DTO_Permission> permission;
    std::vector<Department> department;
};

#endif // DTO_USER_H
