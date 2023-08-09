#ifndef USERDTO_H
#define USERDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct UserDTO
{
    std::string id;
    std::string name;
    std::string avatar;
    std::string image;
    std::vector<std::string> department;
    std::string description;
    std::string email;
    std::vector<std::string> link;
};

#endif // USERDTO_H
