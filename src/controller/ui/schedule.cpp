#include "scheduled_evento.h"
#include "schedule.h"
#include "scheduled_evento_model.h"
#include "convertor.h"

void ScheduleController::loadSchedule()
{
    EventoException err;
    //    ScheduledEventoModel::getInstance()->resetModel(
    //        Convertor<std::vector<DTO_Evento>,
    //                  std::vector<Schedule>>()(
    //            getRepo()->get_subscribed_list(err)
    //    ));

    if ((int)err.code())
    {
        emit loadScheduleErrorEvent(err.message());
        return;
    }

    emit loadScheduleSuccessEvent();
}

void ScheduleController::check(const int eventId, const QString &code)
{
    EventoException err;
    auto isSuccess = getRepo()->event_checkin(eventId, code, err);

    qDebug() << (int)err.code();
    if ((int)err.code())
        return emit checkErrorEvent(err.message());

    if (isSuccess)
        return emit checkSuccessEvent();

    emit checkErrorEvent("密钥错误");
}