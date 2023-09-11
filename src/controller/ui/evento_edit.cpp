#include "evento_edit.h"
#include "evento_edit_helper.h"
#include "evento_exception.h"
#include "repository.h"

void EventoEditController::loadEditInfo(int eventId)
{
    EventoException err;

    auto departmentList = getRepo()->getDepartmentList(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto locationList = getRepo()->getLocationList(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());
    auto typeList = getRepo()->getTypeList(err);
    if ((int)err.code())
        return emit loadEditErrorEvent(err.message());

    EventoEditHelper::getInstance()->updateEventoEdit(departmentList,
                                                      locationList,
                                                      typeList,
                                                      DTO_Evento{});
    emit loadEditSuccessEvent();
}

void EventoEditController::createEvento(QString title,
                                        QString description,
                                        QString eventStart,
                                        QString eventEnd,
                                        QString registerStart,
                                        QString registerEnd,
                                        int typeId,
                                        int loactionId,
                                        QVariantList departmentId,
                                        QString tag,
                                        QVariantList urlList)
{
    emit createSuccessEvent();
}

EventoEditController *EventoEditController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new EventoEditController();
}
