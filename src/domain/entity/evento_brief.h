#ifndef EVENTO_BRIEF_H
#define EVENTO_BRIEF_H

#include "types.h"

struct EventoBrief {
    EventoID id;
    QString title;
    QString description;
    QString time;
    QString location;
    QString department;
    Image image;
};

#endif // EVENTO_BRIEF_H
