#ifndef PARTICIPATEDTO_H
#define PARTICIPATEDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct ParticipateDTO
{
    int id;
    bool isRegistration;
    bool isParticipate;
    bool isSubscribe;
    bool eventId;
    std::string userId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(ParticipateDTO,
                                                id,
                                                isRegistration,
                                                isParticipate,
                                                isSubscribe,
                                                eventId,
                                                userId)

#endif // PARTICIPATEDTO_H
