#ifndef EVENTOBRIEF_H
#define EVENTOBRIEF_H

#include "eventobase.h"
#include "image.h"

struct EventoBrief : EventoBase
{
    QString description;
    QString time;
    Image image;
};

#endif // EVENTOBRIEF_H
