#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eventobase.h"

class Feedback: private EventoBase
{
public:
    Feedback(EventoBase event,
             int score,
             QString comment);

private:
    int m_score;
    QString m_comment;
};

#endif // FEEDBACK_H
