#include "eventobrief.h"

EventoBrief::EventoBrief(EventoID id,
                         EventoState state,
                         QString date,
                         std::optional<QString> image,
                         QString title,
                         QString metadata,
                         bool visible,
                         CheckState checked,
                         QString location,
                         QString type)
: EventoBaseExpand(std::move(id), state, std::move(date),
                   std::move(image), std::move(title),
                   std::move(metadata), visible, checked),
  m_location(std::move(location)), m_type(std::move(type))
{

}
