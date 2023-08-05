#ifndef EVENTOBRIEF_H
#define EVENTOBRIEF_H

#include "eventobaseexpand.h"

class EventoBrief: public EventoBaseExpand
{
public:
    EventoBrief(EventoID id,
                EventoState state,
                QString date,
                std::optional<QString> image,
                QString title,
                QString metadata,
                bool visible,
                CheckState checked,
                QString location,
                QString type);

    QString getLocation() const { return m_location; }

private:
    QString m_location;
    QString m_type;
};

#endif // EVENTOBRIEF_H
