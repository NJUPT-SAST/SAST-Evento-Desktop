#ifndef EVENTO_H
#define EVENTO_H

#include "eventobase.h"

struct Evento : EventoBase
{
    QString description;
    QString time;
    QString type;
    QString location;
    QString tag;
    ParticipationState participate;
    CheckState checked;
};

#endif // EVENTO_H
