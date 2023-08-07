#ifndef EVENTOBRIEF_H
#define EVENTOBRIEF_H

#include "eventobase.h"

struct EventoBrief : EventoBase
{
    QString description;
    QString time;
    QString image;
};

#endif // EVENTOBRIEF_H
