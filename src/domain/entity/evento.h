#ifndef EVENTO_H
#define EVENTO_H

#include "types.h"

struct Evento {
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

    QString title;
    EventState state;
    QString description;
    QString time;
    EventType type;
    QString location;
    QString tag;
    ParticipationState participate;
    CheckState checked;
};

#endif // EVENTO_H
