#ifndef EVENTOBASE_H
#define EVENTOBASE_H

#include <QString>
using EventoID = QString;

class EventoBase
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };

    EventoBase(EventoID id,
               EventoState state,
               QString date,
               std::optional<QString> image,
               QString title,
               QString metadata)
    : m_id(std::move(id)), m_state(state), m_date(std::move(date)),
      m_image(std::move(image)), m_title(std::move(title)),m_metadata(metadata)
    {}

    EventoState getState() { return m_state; }
    QString getDate() { return m_date; }
    QString getImage() { return m_image.value_or("default path"); }
    QString getTitle() { return m_title; }

protected:
    EventoID m_id;
    EventoState m_state;
    QString m_date;
    std::optional<QString> m_image;
    QString m_title;
    QString m_metadata;
};

#endif // EVENTOBASE_H
