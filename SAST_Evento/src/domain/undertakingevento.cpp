#include "undertakingevento.h"

undertakingevento::undertakingevento(EventoID id,
                                     EventoState state,
                                     QString date,
                                     std::optional<QString> image,
                                     QString title,
                                     QString description,
                                     QString metadata,
                                     bool visible)
    :id(std::move(id)),
     state(state),
     date(std::move(date)),
     image(std::move(image)),
     title(std::move(title)),
     description(std::move(description)),
     metadata(std::move(metadata)),
     visible(visible)
{}
