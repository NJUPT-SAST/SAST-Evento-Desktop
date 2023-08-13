#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "evento.h"
#include "image.h"

struct Schedule {
    QString title;
    EventState state;
    QString location;
    QString date;
    QString startTime;
    QString endTime;
    Evento::CheckState checked;
    Image image;
};

#endif // SCHEDULE_H
