#include "scheduled_evento.h"
#include "schedule.h"
#include "scheduled_evento_model.h"
#include "convertor.h"

void ScheduleController::loadRegisteredSchedule()
{
    EventoException err;
    //    ScheduledEventoModel::getInstance()->resetModel(
    //        Convertor<std::vector<DTO_Evento>,
    //                  std::vector<Schedule>>()(
    //            getRepo()->get_registered_list(err)
    //    ));

    if ((int)err.code())
    {
        emit loadRegisteredScheduleErrorEvent(err.message());
        return;
    }

    emit loadRegisteredScheduleSuccessEvent();
}

void ScheduleController::loadSubscribedSchedule()
{
    EventoException err;
    //    ScheduledEventoModel::getInstance()->resetModel(
    //        Convertor<std::vector<DTO_Evento>,
    //                  std::vector<Schedule>>()(
    //            getRepo()->get_subscribed_list(err)
    //    ));

    if ((int)err.code())
    {
        emit loadSubscribedScheduleErrorEvent(err.message());
        return;
    }

    emit loadSubscribedScheduleSuccessEvent();
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

ScheduleController *ScheduleController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

ScheduleController *ScheduleController::getInstance()
{
    static ScheduleController singleton;
    return &singleton;
}
