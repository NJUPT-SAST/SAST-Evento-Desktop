#ifndef EVENTO_H
#define EVENTO_H

#include "types.h"

class DTO_Evento;

struct Evento {
    EventoID id;
    QString title;
    QString description;
    QString eventTime;
    QString registrationTime;
    EventType type;
    QString location;
    Tag tag;
    EventState state;
    QString department;
    Image image;

    Evento() = default;
    Evento(const DTO_Evento&);
};

#endif // EVENTO_H
