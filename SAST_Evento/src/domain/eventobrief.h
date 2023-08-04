#ifndef EVENTOBRIEF_H
#define EVENTOBRIEF_H

#include <QString>
using EventoID = QString;

class EventoBrief
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };

    enum class CheckState {
        Disabled,
        Checked,
        Expired,
        Unchecked,
        Scene
    };

    EventoBrief(EventoID id,
                EventoState state,
                QString date,
                std::optional<QString> image,
                QString title,
                QString location,
                QString type,
                QString metadata,
                bool visible,
                bool enable,
                CheckState checked);
    EventoState getState() const { return m_state; }
    QString getDate() const { return m_date; }
    QString getImage() const { return m_image.value_or("default path"); }
    QString getTitle() const { return m_title; }
    QString getLocation() const { return m_location; }
    CheckState getCheckState() const { return m_checked; }
    bool isEnable() const { return m_enable; }

private:
    EventoID m_id;
    EventoState m_state;
    QString m_date;
    std::optional<QString> m_image;
    QString m_title;
    QString m_location;
    QString m_type;
    QString m_metadata;
    bool m_visible;
    bool m_enable;
    CheckState m_checked;
};

#endif // EVENTOBRIEF_H
