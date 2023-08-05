#ifndef EVENTOHISTORY_H
#define EVENTOHISTORY_H

#include <QString>
using EventoID = QString;


class EventoHistory
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };
    enum class CheckState {
        Disabled,
        Checked,
        Expired,
        Unchecked,
        Scene
    };
    EventoHistory(EventoID id,
                  EventoState state,
                  QString date,
                  std::optional<QString> image,
                  QString title,
                  QString description,
                  QString type,
                  QString metadata,
                  bool visible,
                  bool enabled,
                  CheckState checked);
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
    bool enabled;
    CheckState checked;
};

#endif // EVENTOHISTORY_H

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
            }
*/
