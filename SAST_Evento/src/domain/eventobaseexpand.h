#ifndef EVENTOBASEEXPAND_H
#define EVENTOBASEEXPAND_H

#include "eventobase.h"

class EventoBaseExpand : public EventoBase
{
public:
    enum class CheckState {
        Disabled,
        Checked,
        Expired,
        Unchecked,
        Scene
    };

    EventoBaseExpand(EventoID id,
                     EventoState state,
                     QString date,
                     std::optional<QString> image,
                     QString title,
                     QString metadata,
                     bool visible,
                     CheckState checked)
    : EventoBase(std::move(id), state, std::move(date),
                 std::move(image), std::move(title), std::move(metadata)),
      m_visible(visible), m_checked(checked) {}

    bool isVisible() const { return m_visible; }
    CheckState getCheckState() const { return m_checked; }

protected:
    bool m_visible;
    CheckState m_checked;
};

#endif // EVENTOBASEEXPAND_H
