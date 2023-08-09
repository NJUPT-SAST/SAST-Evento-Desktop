#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "eventobase.h"
#include "image.h"

struct Schedule : EventoBase
{
    QString location;
    QString date;
    QString startTime;
    QString endTime;
    CheckState checked;
    Image image;
};

#endif // SCHEDULE_H
