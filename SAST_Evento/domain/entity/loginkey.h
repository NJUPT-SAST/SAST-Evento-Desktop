#ifndef LOGINKEY_H
#define LOGINKEY_H

#include <infrastructure/nlohmann/json.hpp>

struct LoginKey
{
    std::string uid;
    std::string token;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LoginKey, uid, token)

#endif // LOGINKEY_H
