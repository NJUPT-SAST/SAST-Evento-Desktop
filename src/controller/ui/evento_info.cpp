#include "evento_info.h"
#include "convertor.h"
#include "evento_exception.h"
#include "helper/evento_helper.h"
#include "slide_model.h"

void EventoInfoController::loadEventoInfo(EventoID eventId)
{
    EventoException err;
    // EventoHelper::getInstance()->updateEvento(
    //     Convertor<DTO_Evento, Evento>()(
    //         m_repository->get_event(eventId, err)
    //));

    if ((int)err.code())
    {
        emit loadEventoErrorEvent(err.message());
        return;
    }

    emit loadEventoSuccessEvent();
}
