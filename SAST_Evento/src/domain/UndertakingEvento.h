#ifndef UNDERTAKINGEVENTO_H
#define UNDERTAKINGEVENTO_H

#include <QString>
using EventoID = QString;

class undertakingevento
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };
    undertakingevento(EventoID id,
                      EventoState state,
                      QString date,
                      std::optional<QString> image,
                      QString title,
                      QString description,
                      QString metadata,
                      bool visible);
private:
    EventoID id;
    EventoState state;
    QString date;
    std::optional<QString> image;
    QString title;
    QString description;
    QString metadata;
    bool visible;
};

#endif // UNDERTAKINGEVENTO_H

/*
"UndertakingEvento":{
                    "id":"EventoID",
                    "state":"EventoState",
                    "date":"QString",
                    "image":"std::optional<QString>",
                    "title":"QString",
                    "description":"QString",
                    "metadata":"QString",
                    "visible":"bool"
                },
*/
