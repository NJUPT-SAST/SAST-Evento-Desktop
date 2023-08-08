#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "eventobase.h"

struct Schedule : EventoBase
{
    QString image;
    QString location;
    QString date;
    QString startTime;
    QString endTime;
    CheckState checked;
};

#endif // SCHEDULE_H
