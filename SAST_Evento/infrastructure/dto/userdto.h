#ifndef USERDTO_H
#define USERDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct UserDTO
{
    std::string id;
    std::string name;
    std::string avatar;
    std::vector<std::string> department;
    std::string description;
    std::string email;
    std::vector<std::string> link;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UserDTO, id, name, avatar, department, description, email, link)

#endif // USERDTO_H
