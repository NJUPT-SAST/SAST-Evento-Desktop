#ifndef SLIDES_H
#define SLIDES_H

#include <QString>
using EventoID = QString;

class Slides
{
public:
    Slides(QString id, QString pic, QString title, EventoID eventId, std::optional<QString> link);

private:
    QString m_id;
    QString m_pic;
    QString m_title;
    EventoID m_eventId;
    std::optional<QString> m_link;
};

#endif // SLIDES_H
