#include "eventoschedule.h"
#include "src/controller/eventobriefmodel.h"

EventoSchedule::EventoSchedule()
    : m_eventoBriefModel(EventoBriefModel::getInstance()),
    m_undertakingEventoModel(UndertakingEvento::getInstance()),
    m_latestEventoModel(LatestEvento::getInstance())
{

}

EventoSchedule* EventoSchedule::getInstance()
{
    static EventoSchedule instance;
    return &instance;
}

void EventoSchedule::onClickEvento(EventoID id)
{

}

void EventoSchedule::onCheck(EventoID id)
{

}

void EventoSchedule::onFeedback(EventoID id)
{

}
