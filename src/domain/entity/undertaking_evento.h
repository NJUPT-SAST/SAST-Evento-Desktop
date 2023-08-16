#ifndef UNDERTAKING_EVENTO_H
#define UNDERTAKING_EVENTO_H

#include "types.h"

struct UndertakingEvento {
    EventoID id;
    QString title;
    QString time;
    QString location;
    QString department;
    Image image;
};

#endif // UNDERTAKING_EVENTO_H
