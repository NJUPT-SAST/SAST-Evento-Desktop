#include "calendar.h"
#include "convertor.h"
#include "evento_edit_helper.h"
#include "evento_exception.h"
#include "evento_helper.h"
#include "slide_model.h"

void CalendarController::loadAllEventoInfo(const QString &date)
{
    emit loadAllEventoSuccessEvent();
}

void CalendarController::loadEventoInfo(const EventoID eventId)
{
    EventoException err;
    auto evento = getRepo()->getEvent(eventId, err);
    EventoHelper::getInstance()->updateEvento(Convertor<DTO_Evento, Evento>()(evento),
                                              ParticipationStatus{});

    if (err)
        return emit loadEventoErrorEvent(err.message());
    SlideModel::getInstance()->resetModel(Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(
        getRepo()->getEventSlideList(eventId, err)));
    if (err)
        return emit loadEventoErrorEvent(err.message());

    auto departmentList = getRepo()->getDepartmentList(err);
    if (err)
        return emit loadEventoErrorEvent(err.message());
    auto locationList = getRepo()->getLocationList(err);
    if (err)
        return emit loadEventoErrorEvent(err.message());
    auto typeList = getRepo()->getTypeList(err);
    if (err)
        return emit loadEventoErrorEvent(err.message());

    EventoEditHelper::getInstance()->updateEventoEdit(departmentList,
                                                      locationList,
                                                      typeList,
                                                      evento);
    emit loadEventoSuccessEvent();
}

void CalendarController::deleteEvento(const EventoID eventId)
{
    emit deleteSuccessEvent();
}

QString CalendarController::loadCheckCode(const EventoID eventId)
{
    EventoException err;
    auto code = getRepo()->getQRCode(eventId, err);
    if (err) {
        emit loadCheckCodeErrorEvent(err.message());
        return {};
    }
    emit loadCheckCodeSuccessEvent();
    return code;
}

CalendarController *CalendarController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new CalendarController();
}
