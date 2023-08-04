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
                QString description,
                QString type,
                QString metadata,
                bool visible,
                bool enable,
                CheckState checked);

private:
    EventoID m_id;
    EventoState m_state;
    QString m_date;
    std::optional<QString> m_image;
    QString m_title;
    QString m_description;
    QString m_type;
    QString m_metadata;
    bool m_visible;
    bool m_enable;
    CheckState m_checked;
};

#endif // EVENTOBRIEF_H
