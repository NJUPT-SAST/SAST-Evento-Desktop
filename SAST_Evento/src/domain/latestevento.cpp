#include "latestevento.h"

LatestEvento::LatestEvento(EventoID id,
                           EventoState state,
                           QString date,
                           std::optional<QString> image,
                           QString title,
                           QString metadata,
                           QString location,
                           QString description,
                           bool visible,
                           QString type)
: UndertakingEvento(std::move(id), state, std::move(date),
                    std::move(image), std::move(title), std::move(metadata),
                    std::move(location), std::move(description), visible),
    m_type(std::move(type))
{

}
