#ifndef LESSON_H
#define LESSON_H

#include "types.h"

struct DTO_Evento;

struct EventoLesson {
    EventoID id;
    QStringList departments;
    QString topic;
    QString time;
    QString location;
    Image image;

    EventoLesson() = default;
    EventoLesson(const DTO_Evento&);
};

#endif // LESSON_H
