#include "eventohistory.h"

EventoHistory::EventoHistory(EventoID id,
                             EventoState state,
                             QString date,
                             std::optional<QString> image,
                             QString title,
                             QString metadata,
                             bool visible,
                             CheckState checked,
                             QString description,
                             QString type)
: EventoBaseExpand(std::move(id), state, std::move(date),
                   std::move(image), std::move(title),
                   std::move(metadata), visible, checked),
  m_description(std::move(description)),
  m_type(std::move(type))
{

}
