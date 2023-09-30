#ifndef DTO_EVENTO_H
#define DTO_EVENTO_H

#include "types.h"

struct DTO_Evento {
    EventoID id;
    QString title;
    QString description;
    QString gmtEventStart;
    QString gmtEventEnd;
    QString gmtRegistrationStart;
    QString gmtRegistrationEnd;
    EventType type;
    QString location;
    Tag tag;
    QString state;
    std::vector<Department> departments;
};

#endif // DTO_EVENTO_H
