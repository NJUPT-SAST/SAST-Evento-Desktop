#include "undertakingevento.h"

UndertakingEvento::UndertakingEvento(EventoID id,
                                      EventoState state,
                                      QString date,
                                      std::optional<QString> image,
                                      QString title,
                                      QString metadata,
                                      QString location,
                                      QString description,
                                      bool visible)
    : EventoBase(std::move(id), state, std::move(date),
                 std::move(image), std::move(title), std::move(metadata)),
    m_location(std::move(location)),
    m_description(std::move(description)),
    m_visible(visible)
{

}
