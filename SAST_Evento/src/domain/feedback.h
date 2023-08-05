#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QString>
using EventoID = QString;

class Feedback
{
public:
    struct EventInfo {
        EventoID id;
        QString date;
        std::optional<QString> image;
        QString title;
        QString metadata;
    };

    Feedback(EventInfo event,
             int score,
             QString comment);
    EventInfo getEvent() const { return m_event; }
    int getScore() const { return m_score; }
    QString getComment() const { return m_comment; }

private:
    EventInfo m_event;
    int m_score;
    QString m_comment;
};

#endif // FEEDBACK_H
