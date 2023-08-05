#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eventobase.h"

class Feedback: private EventoBase
{
public:
    Feedback(EventoBase event,
             int score,
             QString comment);
    EventInfo getEvent() const { return m_event; }
    int getScore() const { return m_score; }
    QString getComment() const { return m_comment; }

private:
    int m_score;
    QString m_comment;
};

#endif // FEEDBACK_H
