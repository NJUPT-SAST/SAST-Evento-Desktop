#ifndef EVENTO_H
#define EVENTO_H

#include "types.h"

struct Evento {
    EventoID id;
    QString title;
    EventState state;
    QString description;
    QString eventTime;
    QString registerTime;
    QString department;
    QString location;
    EventType type;
    Tag tag;
};

#endif // EVENTO_H
