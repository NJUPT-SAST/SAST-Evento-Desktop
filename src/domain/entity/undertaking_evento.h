#ifndef UNDERTAKING_EVENTO_H
#define UNDERTAKING_EVENTO_H

#include "types.h"

struct DTO_Evento;

struct UndertakingEvento {
    EventoID id;
    QString title;
    QString time;
    QString location;
    QString department;
    Image image;

    UndertakingEvento() = default;
    UndertakingEvento(const DTO_Evento&);
};

#endif // UNDERTAKING_EVENTO_H
