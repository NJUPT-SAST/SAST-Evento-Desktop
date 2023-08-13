#ifndef EVENTO_BRIEF_H
#define EVENTO_BRIEF_H

#include "evento.h"
#include "image.h"

struct EventoBrief {    
    QString title;
    EventState state;
    QString description;
    QString time;
    Image image;
};

#endif // EVENTO_BRIEF_H
