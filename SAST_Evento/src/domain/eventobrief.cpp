#include "eventobrief.h"

EventoBrief::EventoBrief(EventoID id,
                         EventoState state,
                         QString date,
                         std::optional<QString> image,
                         QString title,
                         QString description,
                         QString type,
                         QString metadata,
                         bool visible,
                         bool enable,
                         CheckState checked)
: m_id(std::move(id)), m_state(state), m_date(std::move(date)),
  m_image(std::move(image)), m_title(std::move(title)),
  m_description(std::move(description)), m_type(std::move(type)),
  m_metadata(metadata), m_visible(visible), m_enable(enable),
  m_checked(checked) {}
