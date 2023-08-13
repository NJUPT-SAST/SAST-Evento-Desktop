#ifndef UNDERTAKING_EVENTO_H
#define UNDERTAKING_EVENTO_H

#include "evento.h"
#include "image.h"

struct UndertakingEvento {    
    QString title;
    EventState state;
    QString time;
    QString location;
    Image image;
};

#endif // UNDERTAKING_EVENTO_H
