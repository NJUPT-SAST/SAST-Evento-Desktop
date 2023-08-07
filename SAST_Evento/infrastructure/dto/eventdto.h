#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct EventDTO
{
    int id;
    std::string title;
    std::string description;
    std::string gmtEventStart;
    std::string gmtEventEnd;
    std::string gmtRegistrationStart;
    std::string gmtRegistrationEnd;
    int typeId;
    int locationId;
    std::string tag;
    int state;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(EventDTO,
                                                id,
                                                title,
                                                description,
                                                gmtEventStart,
                                                gmtEventEnd,
                                                gmtRegistrationStart,
                                                gmtRegistrationEnd,
                                                typeId,
                                                locationId,
                                                tag,
                                                state)

#endif // EVENTDTO_H
