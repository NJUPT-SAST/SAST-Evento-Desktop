#ifndef EVENTOHISTORY_H
#define EVENTOHISTORY_H

#include "eventobaseexpand.h"

class EventoHistory : public EventoBaseExpand
{
public:
    EventoHistory(EventoID id,
                  EventoState state,
                  QString date,
                  std::optional<QString> image,
                  QString title,
                  QString metadata,
                  bool visible,
                  CheckState checked,
                  QString description,
                  QString type);
private:
    QString m_description;
    QString m_type;
};

#endif // EVENTOHISTORY_H
