#include "evento_edit.h"
#include "evento_edit_helper.h"
#include "evento_exception.h"
#include "repository.h"

void EventoEditController::loadEditInfo(int eventId)
{
    EventoException err;

    auto departmentList = getRepo()->get_department_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto locationList = getRepo()->get_location_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto typeList = getRepo()->get_type_list(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());

    EventoEditHelper::getInstance()->updateEventoEdit(departmentList,
                                                      locationList,
                                                      typeList,
                                                      DTO_Evento{});
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
