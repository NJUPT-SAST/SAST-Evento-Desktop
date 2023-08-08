#ifndef UNDERTAKINGEVENTO_H
#define UNDERTAKINGEVENTO_H

#include "eventobase.h"
#include "image.h"

struct UndertakingEvento : EventoBase
{
    QString time;
    QString location;
    Image image;
};

#endif // UNDERTAKINGEVENTO_H
