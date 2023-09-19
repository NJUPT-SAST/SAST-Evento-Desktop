#ifndef LATEST_EVENTO_H
#define LATEST_EVENTO_H

#include "types.h"

struct DTO_Evento;

struct LatestEvento {
    EventoID id;
    QString title;
    QString time;
    QString department;
    QString description;
    Image image;

    LatestEvento() = default;
    LatestEvento(const DTO_Evento&);
};

#endif // LATEST_EVENTO_H
