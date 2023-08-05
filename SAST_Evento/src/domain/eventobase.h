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
        m_image(std::move(image)), m_title(std::move(title)),
        m_metadata(std::move(metadata))
    {}

    EventoID getEventoID() const { return m_id; }
    EventoState getState() const { return m_state; }
    QString getDate() const { return m_date; }
    QString getImage() const { return m_image.value_or("default path"); }
    QString getTitle() const { return m_title; }
    QString getMetadata() const { return m_metadata; }

protected:
    EventoID m_id;
    EventoState m_state;
    QString m_date;
    std::optional<QString> m_image;
    QString m_title;
    QString m_metadata;
};

#endif // EVENTOBASE_H
