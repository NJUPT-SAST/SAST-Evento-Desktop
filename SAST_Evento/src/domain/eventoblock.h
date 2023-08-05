#ifndef EVENTOBLOCK_H
#define EVENTOBLOCK_H

#include <QString>
using EventoID = QString;

class EventoBlock
{
public:
    enum class CalendarMode {
        Overall,
        Mine
    };

    EventoBlock(EventoID id,
                int rowStart,
                int rowEnd,
                int columnStart,
                int columnEnd,
                QString data,
                QString title,
                QString description,
                QString metadata,
                bool finished);
    int getRowStart() const { return m_rowStart; }
    int getRowEnd() const { return m_rowEnd; }
    int getColumnStart() const { return m_columnStart; }
    int getColumnEnd() const { return m_columnEnd; }
    QString getData() const { return m_data; }
    QString getTitle() const { return m_title; }
    QString getDescription() const { return m_description; }
    QString getMetaData() const { return m_metadata; }
    bool isFinished() const { return m_finished; }

private:
    EventoID m_id;
    int m_rowStart;
    int m_rowEnd;
    int m_columnStart;
    int m_columnEnd;
    QString m_data;
    QString m_title;
    QString m_description;
    QString m_metadata;
    bool m_finished;
};

#endif // EVENTOBLOCK_H
