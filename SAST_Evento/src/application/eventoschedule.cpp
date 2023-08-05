#include "eventoschedule.h"
#include "src/controller/eventobriefmodel.h"

EventoSchedule::EventoSchedule()
    : m_eventoBriefModel(EventoBriefModel::getInstance()),
    m_undertakingEventoModel(UndertakingEvento::getInstance()),
    m_latestEventoModel(LatestEvento::getInstance())
{

}

void EventoSchedule::onClickEvento(EventoID)
{

}

void EventoSchedule::onCheck(EventoID)
{

}

void EventoSchedule::onFeedback(EventoID)
{

}
