#ifndef EVENTO_BLOCK_H
#define EVENTO_BLOCK_H

#include "types.h"

struct EventoBlock {
    EventoID id;
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
