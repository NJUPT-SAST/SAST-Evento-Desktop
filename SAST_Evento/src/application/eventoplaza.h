#ifndef EVENTOPLAZA_H
#define EVENTOPLAZA_H

#include "src/controller/slidesmodel.h"

class EventoPlaza
{
public:
    EventoPlaza();
private:
    std::shared_ptr<SlidesModel> m_slidesModel;
    std::shared_ptr<UndertakingEvento> m_undertakingEventoModel;
    std::shared_ptr<LatestEvento> m_latestEventoModel;
};

#endif // EVENTOPLAZA_H
