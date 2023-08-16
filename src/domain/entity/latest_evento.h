#ifndef LATEST_EVENTO_H
#define LATEST_EVENTO_H

#include "types.h"

struct LatestEvento {
    EventoID id;
    QString title;
    QString time;
    QString department;
    QString description;
    Image image;
};

#endif // LATEST_EVENTO_H
