#ifndef EVENTO_BRIEF_H
#define EVENTO_BRIEF_H

#include "types.h"

struct DTO_Evento;

struct EventoBrief {
    EventoID id;
    QString title;
    QString description;
    QString time;
    QString location;
    QString department;
    Image image;

    EventoBrief() = default;
    EventoBrief(const DTO_Evento&);
};

#endif // EVENTO_BRIEF_H
