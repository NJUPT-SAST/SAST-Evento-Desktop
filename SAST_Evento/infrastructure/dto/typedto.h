#ifndef TYPEDTO_H
#define TYPEDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct TypeDTO
{
    int id;
    std::string typeName;
    bool allowConflict;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TypeDTO, id, typeName, allowConflict)

#endif // TYPEDTO_H
