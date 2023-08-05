#ifndef EVENTO_H
#define EVENTO_H

#include <QStringList>
#include "eventobrief.h"

class Evento : public EventoBrief
{
public:
    enum class ParticipationState {
        unsubscribed,
        subscribed,
        applied,
        checked,
        finished
    };

    Evento(EventoID id,
           EventoState state,          
           QString date,          
           std::optional<QString> image,
           QString title,
           bool visible,
           CheckState checked,
           QString type,
           QString location,
           QString registration,
           QStringList tag,
           QString description,
           ParticipationState participate,
           bool feedback);

private:
    QString m_registration;
    QStringList m_tag;
    QString m_description;
    ParticipationState m_participate;
    bool m_feedback;
};

#endif // EVENTO_H
