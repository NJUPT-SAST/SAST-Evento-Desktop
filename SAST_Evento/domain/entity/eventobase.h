#ifndef EVENTOBASE_H
#define EVENTOBASE_H

#include <QString>
#include <QDateTime>

struct EventoBase
{
    enum class EventState
    {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };

    int id;
    QString title;
    EventState state;
};

#endif // EVENTOBASE_H
