#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <infrastructure/nlohmann/json.hpp>
#include "typedto.h"
#include "locationdto.h"
#include "departmentdto.h"

struct EventDTO
{
    int id;
    std::string title;
    std::string description;
    std::string gmtEventStart;
    std::string gmtEventEnd;
    std::string gmtRegistrationStart;
    std::string gmtRegistrationEnd;
    TypeDTO type;
    LocationDTO location;
    std::string tag;
    int state;
    std::vector<DepartmentDTO> departments;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(EventDTO,
                                                id,
                                                title,
                                                description,
                                                gmtEventStart,
                                                gmtEventEnd,
                                                gmtRegistrationStart,
                                                gmtRegistrationEnd,
                                                type,
                                                location,
                                                tag,
                                                state,
                                                departments)

#endif // EVENTDTO_H
