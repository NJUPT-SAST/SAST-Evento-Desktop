#ifndef LOCATIONDTO_H
#define LOCATIONDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct LocationDTO
{
    int id;
    std::string locationName;
    int parentId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LocationDTO, id, locationName, parentId)

#endif // LOCATIONDTO_H
