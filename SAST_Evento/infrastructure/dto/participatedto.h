#ifndef PARTICIPATEDTO_H
#define PARTICIPATEDTO_H

#include <QString>

struct ParticipateDTO
{
    int id;
    bool isRegistration;
    bool isParticipate;
    bool isSubscribe;
    bool eventId;
    QString userId;
};

#endif // PARTICIPATEDTO_H
