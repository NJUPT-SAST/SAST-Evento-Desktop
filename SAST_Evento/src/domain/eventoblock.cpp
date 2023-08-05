#include "eventoblock.h"

EventoBlock::EventoBlock(EventoID id,
                         int rowStart,
                         int rowEnd,
                         int columnStart,
                         int columnEnd,
                         QString data,
                         QString title,
                         QString description,
                         QString metadata,
                         bool finished)
: m_id(std::move(id)),m_rowStart(rowStart),m_rowEnd(rowEnd),
  m_columnStart(columnStart),m_columnEnd(columnEnd),m_data(data),
  m_title(std::move(title)),m_description(std::move(description)),m_metadata(metadata),
  m_finished(finished){}

