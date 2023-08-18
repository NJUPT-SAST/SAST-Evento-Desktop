#include "evento_info.h"
#include "local/repositoryimpl.h"
#include "convertor.h"
#include "evento_exception.h"
#include "helper/evento_helper.h"

EventoInfoController::EventoInfoController(QObject *parent)
    : m_repository(new repositoryImpl)
{

}

void EventoInfoController::loadEventoInfo(int eventId)
{
    EventoException err;
    EventoHelper::getInstance()->updateEvento(
        Convertor<DTO_Evento, Evento>()(
            m_repository->get_event(eventId, err)
    ));

    if ((int)err.code()) {
        emit loadEventoErrorEvent(err.message());
        return;
    }
    emit loadEventoSuccessEvent();
}

EventoInfoController::~EventoInfoController() = default;
