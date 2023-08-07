#ifndef LOGINKEYDTO_H
#define LOGINKEYDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct LoginKeyDTO
{
    std::string uid;
    std::string token;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LoginKeyDTO, uid, token)

#endif // LOGINKEYDTO_H
