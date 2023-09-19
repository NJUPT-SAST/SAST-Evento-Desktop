#ifndef SCHEDULED_EVENTO_H
#define SCHEDULED_EVENTO_H

#include "types.h"

struct DTO_Evento;

struct Schedule
{
    EventoID id;
    QString title;
    EventState state;
    QString department;
    QString location;
    QString date;
    QString startTime;
    QString endTime;
    bool isChecked;
    bool hasFeedback;

    Schedule() = default;
    Schedule(const DTO_Evento&);
};

#endif // SCHEDULED_EVENTO_H
