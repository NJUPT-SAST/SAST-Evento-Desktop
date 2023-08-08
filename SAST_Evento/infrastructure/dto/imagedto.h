#ifndef IMAGEDTO_H
#define IMAGEDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct ImageDTO
{
    int id;
    std::string title;
    std::string url;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(ImageDTO, id, title, url);

#endif // IMAGEDTO_H
