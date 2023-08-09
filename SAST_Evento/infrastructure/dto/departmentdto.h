#ifndef DEPARTMENTDTO_H
#define DEPARTMENTDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct DepartmentDTO
{
    int id;
    std::string departmentName;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(DepartmentDTO, id, departmentName)

#endif // DEPARTMENTDTO_H
