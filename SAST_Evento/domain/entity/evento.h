#ifndef EVENTO_H
#define EVENTO_H

#include "eventobase.h"

struct Evento : EventoBase
{
    enum class ParticipationState {
        Unsubscribed,
        Subscribed,
        Checked,
        Over
    };

    enum class CheckState {
        Disabled,
        Checked,
        Expired,
        Unchecked
    };

    QString description;
    QString time;
    QString type;
    QString location;
    QString tag;
    ParticipationState participate;
    CheckState checked;
};

#endif // EVENTO_H
