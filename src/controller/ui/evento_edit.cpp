#include "evento_edit.h"
#include "evento_exception.h"
#include "evento_edit_helper.h"
#include "evento_helper.h"
#include "repository.h"
#include "convertor.h"
#include "slide_model.h"

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
        if ((int)err.code())
            return emit loadEditErrorEvent(err.message());
        SlideModel::getInstance()->resetModel(
            Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(
                getRepo()->get_event_slide_list(eventId, err)
        ));
        if ((int)err.code())
            return emit loadEditErrorEvent(err.message());
    }

    auto departmentList = getRepo()->get_department_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto locationList = getRepo()->get_location_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto typeList = getRepo()->get_type_list(err);
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

void EventoEditController::createEvento(const QString &title,
                                        const QString &description,
                                        const QString &eventStart,
                                        const QString &eventEnd,
                                        const QString &registerStart,
                                        const QString &registerEnd,
                                        int typeId,
                                        int loactionId,
                                        const QVariantList &departmentId,
                                        const QString &tag)
{
    emit createSuccessEvent();
}

EventoEditController *EventoEditController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new EventoEditController();
}
