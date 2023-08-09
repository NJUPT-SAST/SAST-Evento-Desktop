#include "eventocontroller.h"
#include "infrastructure/helper/evento_helper.h"

EventoController::EventoController(QObject *parent)
    : BaseController{parent}
{

}

void EventoController::loadEventoInfo(int eventId)
{
    try {
        Evento evento = m_eventService()->loadEvento(eventId);
        EventoHelper::getInstance()->updateEvento(evento);
        Q_EMIT loadEventoSuccessEvent();
    } catch(const BizException& e) {
        Q_EMIT loadEventoErrorEvent(e.message);
    }
}
