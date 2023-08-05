#include "eventoblock.h"

EventoBlock::EventoBlock(EventoID id,
                         int start,
                         int end,
                         int data,
                         QString title,
                         QString description,
                         QString metadata,
                         bool finished,
                         bool enabled)
: m_id(std::move(id)),m_start(start),m_end(end),m_data(data),
  m_title(std::move(title)),m_description(std::move(description)),m_metadata(metadata),
  m_finished(finished),m_enabled(enabled){}

