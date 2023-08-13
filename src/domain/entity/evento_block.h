#ifndef EVENTO_BLOCK_H
#define EVENTO_BLOCK_H

#include "evento.h"

struct EventoBlock {
    QString title;
    EventState state;
    QString data;
    QString time;
    QString location;
    QString department;
    int rowStart;
    int rowEnd;
    int colunmStart;
    int colunmEnd;
    bool finished;
    bool editable;
};

#endif // EVENTOBLOCK_H
