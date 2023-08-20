#include "src/controller/ui/schedule.h"
#include "src/domain/entity/schedule.h"
#include "scheduled_evento_model.h"
#include "convertor.h"
#include "local/repositoryimpl.h"

ScheduleController::ScheduleController(QObject *parent)
    :m_repository(new repositoryImpl)
{

}

void ScheduleController::loadSchedule()
{
    EventoException err;
//    ScheduledEventoModel::getInstance()->resetModel(
//        Convertor<std::vector<DTO_Evento>,
//                  std::vector<Schedule>>()(
//            m_repository->get_subscribed_list(err)
//    ));

    if ((int)err.code()) {
        emit loadScheduleErrorEvent(err.message());
        return;
    }

    emit loadScheduleSuccessEvent();
}

void ScheduleController::check(const int eventId, const QString &code)
{
    EventoException err;
    auto isSuccess = m_repository->event_checkin(eventId, code, err);

    qDebug() << (int)err.code();
    if ((int)err.code())
        return emit checkErrorEvent(err.message());

    if (isSuccess)
        return emit checkSuccessEvent();

    emit checkErrorEvent("密钥错误");
}

ScheduleController::~ScheduleController() = default;
