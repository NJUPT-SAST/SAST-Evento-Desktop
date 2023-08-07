#ifndef PERMISSIONDTO_H
#define PERMISSIONDTO_H

#include <infrastructure/nlohmann/json.hpp>
#include <QStringList>

struct PermissionDTO
{
    int id;
    std::vector<std::string> allMethodName;
    std::string userId;
    int eventId;
    std::string gmtUpdate;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(PermissionDTO, id, allMethodName, userId, eventId, gmtUpdate)

#endif // PERMISSIONDTO_H
