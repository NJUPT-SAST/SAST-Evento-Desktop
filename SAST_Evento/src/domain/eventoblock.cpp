#include "eventoblock.h"

EventoBlock::EventoBlock(EventoID id, EventoState state, QString date,
                         QString title, QString metadata, int rowStart,
                         int rowEnd, int columnStart, int columnEnd,
                         QString description, bool finished)
    : EventoBase(std::move(id), state, std::move(date), std::nullopt,
                 std::move(title), std::move(metadata)),
      m_rowStart(rowStart),
      m_rowEnd(rowEnd),
      m_columnStart(columnStart),
      m_columnEnd(columnEnd),
      m_description(std::move(description)),
      m_finished(finished) {}
