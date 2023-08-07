#ifndef UNDERTAKINGEVENTO_H
#define UNDERTAKINGEVENTO_H

#include "eventobase.h"

struct UndertakingEvento : EventoBase
{
    QString time;
    QString location;
    QStringList image;
};

#endif // UNDERTAKINGEVENTO_H
