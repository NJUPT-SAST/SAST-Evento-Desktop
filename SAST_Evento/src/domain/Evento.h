#ifndef EVENTO_H
#define EVENTO_H

#include <QString>
#include <QStringList>

using EventoID = QString;

class Evento
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };
    enum class ParticipationState {
        unsubscribed,
        subscribed,
        applied,
        checked,
        finished
    };

    Evento(EventoID id,
           EventoState state,
           QStringList tag,
           QString date,
           QString registration,
           std::optional<QString> image,
           QString title,
           QString description,
           QString type,
           QString location,
           bool visible,
           ParticipationState participate,
           bool feedback);

private:
    EventoID id;
    EventoState state;
    QStringList tag;
    QString date;
    QString registration;
    std::optional<QString> image;
    QString title;
    QString description;
    QString type;
    QString location;
    bool visible;
    ParticipationState participate;
    bool feedback;
};

#endif // EVENTO_H
