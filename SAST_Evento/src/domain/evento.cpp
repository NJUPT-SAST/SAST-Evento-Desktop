#include "evento.h"

Evento::Evento(EventoID id,
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
               bool feedback)
     :id(std::move(id)),
      state(state),
      tag(std::move(tag)),
      date(std::move(date)),
      registration(std::move(registration)),
      image(std::move(image)),
      title(std::move(title)),
      description(std::move(description)),
      type(std::move(type)),
      location(std::move(location)),
      visible(visible),
      participate(std::move(participate)),
      feedback(feedback)
{}


/*

    EventoID id;
    EventoSate state;
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
*/
