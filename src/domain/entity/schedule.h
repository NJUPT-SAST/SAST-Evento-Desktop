#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "types.h"

struct Schedule {
    EventoID id;
    QString title;
    EventState state;
    QString department;
    QString location;
    QString startTime;
    QString endTime;
    Image image;
};

#endif // SCHEDULE_H
