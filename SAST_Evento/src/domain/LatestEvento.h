#ifndef LATESTEVENTO_H
#define LATESTEVENTO_H

#include <QString>
using EventoID = QString;

class latestevento
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };
    latestevento(EventoID id,
                      EventoState state,
                      QString date,
                      std::optional<QString> image,
                      QString title,
                      QString description,
                      QString type,
                      QString metadata,
                      bool visible);
private:
    EventoID id;
    EventoState state;
    QString date;
    std::optional<QString> image;
    QString title;
    QString description;
    QString type;
    QString metadata;
    bool visible;
};

#endif // LATESTEVENTO_H
