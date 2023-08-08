#ifndef LATESTEVENTO_H
#define LATESTEVENTO_H

#include "eventobase.h"

struct LatestEvento : EventoBase
{
    QString time;
    QString description;
    QString image;
};

#endif // LATESTEVENTO_H
