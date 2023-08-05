#ifndef EVENTOBLOCK_H
#define EVENTOBLOCK_H

#include "eventobase.h"

class EventoBlock : EventoBase {
public:
    enum class CalendarMode { Overall, Mine };

    EventoBlock(EventoID id,
                EventoState state,
                QString date,
                QString title,
                QString metadata,
                int rowStart,
                int rowEnd,
                int columnStart,
                int columnEnd,
                QString description,
                bool finished);

    int getRowStart() const { return m_rowStart; }
    int getRowEnd() const { return m_rowEnd; }
    int getColumnStart() const { return m_columnStart; }
    int getColumnEnd() const { return m_columnEnd; }
    QString getDate() const { return m_date; }
    QString getTitle() const { return m_title; }
    QString getDescription() const { return m_description; }
    bool isFinished() const { return m_finished; }

    void setRowStart(int rowStart);
    void setRowEnd(int rowEnd);
    void setColumnStart(int columnStart);
    void setColumnEnd(int columnEnd);

private:
    int m_rowStart;
    int m_rowEnd;
    int m_columnStart;
    int m_columnEnd;
    QString m_description;
    bool m_finished;
};

#endif  // EVENTOBLOCK_H
