#ifndef LATESTEVENTO_H
#define LATESTEVENTO_H

#include "eventobase.h"
#include "image.h"

struct LatestEvento : EventoBase
{
    QString time;
    QString description;
    Image image;
};

#endif // LATESTEVENTO_H
