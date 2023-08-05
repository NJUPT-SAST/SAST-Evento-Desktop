#ifndef LATESTEVENTO_H
#define LATESTEVENTO_H

#include "undertakingevento.h"

class LatestEvento : public UndertakingEvento
{
public:
    LatestEvento(EventoID id,
                 EventoState state,
                 QString date,
                 std::optional<QString> image,
                 QString title,
                 QString metadata,
                 QString location,
                 QString description,
                 bool visible,
                 QString type);
private:
    QString m_type;
};

#endif // LATESTEVENTO_H
