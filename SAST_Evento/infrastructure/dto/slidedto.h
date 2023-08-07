#ifndef SLIDEDTO_H
#define SLIDEDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct SlideDTO
{
    int id;
    std::string title;
    std::string link;
    std::string url;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SlideDTO, id, title, link, url)

#endif // SLIDEDTO_H
