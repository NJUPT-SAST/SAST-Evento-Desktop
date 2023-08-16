#ifndef EVENTO_BRIEF_H
#define EVENTO_BRIEF_H

#include "types.h"

struct EventoBrief {
    EventoID id;
    QString title;
    EventState state;
    QString description;
    QString time;
    Image image;
};

#endif // EVENTO_BRIEF_H
