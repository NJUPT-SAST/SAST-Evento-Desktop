#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <QString>

struct EventDTO
{
    int id;
    QString title;
    QString description;
    QString gmtEventStart;
    QString gmtEventEnd;
    QString gmtRegistrationStart;
    QString gmtRegistrationEnd;
    int typeId;
    int locationId;
    QString tag;
    int state;
};

#endif // EVENTDTO_H
