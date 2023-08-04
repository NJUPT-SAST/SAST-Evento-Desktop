#include "slides.h"

Slides::Slides(QString id, QString pic, QString title, EventoID eventId, std::optional<QString> link)
    : m_id(std::move(id)), m_title(std::move(title)),
    m_eventId(std::move(eventId)), m_link(std::move(link)) {}

QString Slides::getLink() const
{
    if (m_link.has_value())
        return m_link.value();
    return "defalut path";
    // TODO: default path
}
