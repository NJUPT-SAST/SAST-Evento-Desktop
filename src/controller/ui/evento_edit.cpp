#include "evento_edit.h"
#include "evento_exception.h"
#include "evento_edit_helper.h"
#include "evento_helper.h"
#include "repository.h"
#include "convertor.h"

void EventoEditController::loadEditInfo(int eventId)
{
    EventoException err;
    auto evento = DTO_Evento();
    if (eventId != 0) {
        evento = getRepo()->get_event(eventId, err);
        EventoHelper::getInstance()->updateEvento(
            Convertor<DTO_Evento, Evento>()(evento),
            ParticipationStatus{}
        );
    }
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());

    auto departmentList = getRepo()->get_department_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto locationList = getRepo()->get_location_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto typeList = getRepo()->get_type_list(1, 10, err); // FIX ME
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());

    EventoEditHelper::getInstance()->updateEventoEdit(
        departmentList,
        locationList,
        typeList,
        evento
    );
    emit loadEditSuccessEvent();
}

EventoEditController *EventoEditController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new EventoEditController();
}
