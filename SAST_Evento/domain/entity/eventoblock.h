#ifndef EVENTOBLOCK_H
#define EVENTOBLOCK_H

#include "eventobase.h"

struct EventoBlock : EventoBase
{
    QString data;
    QString time;
    QString department;
    int rowStart;
    int rowEnd;
    int colunmStart;
    int colunmEnd;
    bool finished;
    bool editable;
};

#endif // EVENTOBLOCK_H
