#ifndef EVENTOPLAZA_H
#define EVENTOPLAZA_H

#include <QObject>

class SlidesModel;
class UndertakingEvento;
class LatestEvento;

class EventoPlaza
{
    Q_OBJECT

public:
    using EventoID = QString;

    static EventoPlaza* getInstance();

    ~EventoPlaza() = default;

public slots:
    void onClickEvento(EventoID);
    void onClickSlide(QString);

private:
    EventoPlaza();

    SlidesModel* m_slidesModel;
    UndertakingEvento* m_undertakingEventoModel;
    LatestEvento* m_latestEventoModel;
};

#endif // EVENTOPLAZA_H
