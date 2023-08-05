#ifndef EVENTOBLOCK_H
#define EVENTOBLOCK_H

#include "eventobase.h"

class EventoBlock: EventoBase
{
public:
    enum class CalendarMode {
        Overall,
        Mine
    };

    EventoBlock(EventoID id,
                EventoState state,
                QString date,
                QString title,
                QString metadata,
                int rowStart,
                int rowEnd,
                int columnStart,
                int columnEnd,
                QString description,              
                bool finished);

private:
    int m_rowStart;
    int m_rowEnd;
    int m_columnStart;
    int m_columnEnd;
    QString m_description;
    bool m_finished;
};

#endif // EVENTOBLOCK_H
