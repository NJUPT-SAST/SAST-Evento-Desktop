#ifndef UNDERTAKINGEVENTO_H
#define UNDERTAKINGEVENTO_H

#include "eventobase.h"

class UndertakingEvento: public EventoBase
{
public:
    UndertakingEvento(EventoID id,
                       EventoState state,
                       QString date,
                       std::optional<QString> image,
                       QString title,
                       QString metadata,
                       QString location,
                       QString description,
                       bool visible);

    QString getLocation() const { return m_location; }

private:
    QString m_location;
    QString m_description;
    bool m_visible;
};

#endif // UNDERTAKINGEVENTO_H
