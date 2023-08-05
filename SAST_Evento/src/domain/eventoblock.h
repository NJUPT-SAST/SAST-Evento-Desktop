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
                int start,
                int end,
                int data,
                QString title,
                QString description,
                QString metadata,
                bool finished,
                bool enabled);

private:
    EventoID m_id;
    int m_start;
    int m_end;
    int m_data;
    QString m_title;
    QString m_description;
    QString m_metadata;
    bool m_finished;
    bool m_enabled;
};

#endif // EVENTOBLOCK_H
