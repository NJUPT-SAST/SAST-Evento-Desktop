#ifndef EVENTO_IN_PROGRESS_H
#define EVENTO_IN_PROGRESS_H

#include "types.h"

struct DTO_Evento;

struct EventoInProgress {
    EventoID id;
    QString title;
    QString time;
    QString location;
    QString department;
    Image image;

    EventoInProgress() = default;
    EventoInProgress(const DTO_Evento&);
};

#endif // EVENTO_IN_PROGRESS_H
