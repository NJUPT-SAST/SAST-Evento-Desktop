#ifndef LOGINKEY_H
#define LOGINKEY_H

#include <infrastructure/nlohmann/json.hpp>

struct LoginKeyDTO
{
    std::string uid;
    std::string token;
    std::vector<std::string> basicPermissions;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LoginKeyDTO, uid, token, basicPermissions)

#endif // LOGINKEY_H
