#include "eventohistory.h"

EventoHistory::EventoHistory(EventoID id,
              EventoState state,
              QString date,
              std::optional<QString> image,
              QString title,
              QString description,
              QString type,
              QString metadata,
              bool visible,
              bool enabled,
              CheckState checked)
    :id(std::move(id)),
     state(state),
     date(std::move(date)),
     image(std::move(image)),
     title(std::move(title)),
     description(std::move(description)),
     type(std::move(type)),
     metadata(std::move(metadata)),
     visible(visible),
     enabled(enabled),
     checked(checked)
{}

/*
"EventoHistory":{
                    "id":"EventoID",
                    "state":"EventoSate"
                    "date":"QString",
                    "image":"std::optional<QString>",
                    "title":"QString",
                    "description":"QString",
                    "type":"QString",
                    "metadata":"QString",
                    "visible":"bool",
                    "enabled":"bool",
                    "Checked":"CheckSate"
                }
*/
