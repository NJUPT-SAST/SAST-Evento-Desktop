#include "evento.h"

Evento::Evento(EventoID id,
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
               bool feedback)
    : EventoBrief(std::move(id), state, std::move(date),
                       std::move(image), std::move(title), nullptr,
                  visible, checked, std::move(type), std::move(location)),
    m_registration(std::move(registration)), m_tag(std::move(tag)),
    m_participate(participate), m_feedback(feedback)
{

}
