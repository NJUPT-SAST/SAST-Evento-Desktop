#ifndef EVENTOPLAZA_H
#define EVENTOPLAZA_H

class SlidesModel;
class UndertakingEvento;
class LatestEvento;

class EventoPlaza
{
public:
    EventoPlaza();
private:
    SlidesModel* m_slidesModel;
    UndertakingEvento* m_undertakingEventoModel;
    LatestEvento* m_latestEventoModel;
};

#endif // EVENTOPLAZA_H
