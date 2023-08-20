#ifndef SCHEDULED_EVENTO_H
#define SCHEDULED_EVENTO_H

#include "types.h"

struct Schedule {
    EventoID id;
    QString title;
    EventState state;
    QString department;
    QString location;
    QString date;
    QString startTime;
    QString endTime;
    bool isChecked;
    bool isFeedback;
};

#endif  // SCHEDULED_EVENTO_H
