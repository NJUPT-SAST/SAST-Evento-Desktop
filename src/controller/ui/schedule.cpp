#include "src/controller/ui/schedule.h"
#include "src/domain/entity/schedule.h"
#include "scheduled_evento_model.h"
#include "convertor.h"
#include "local/repositoryimpl.h"

ScheduleController::ScheduleController(QObject *parent)
    :m_repository(new repositoryImpl)
{

}

void ScheduleController::loadSchedule(int eventId)
{
    EventoException err;
//    ScheduledEventoModel::getInstance()->resetModel(
//        Convertor<std::vector<DTO_Evento>,
//                  std::vector<Schedule>>()(
//            m_repository->get_event(eventId, err)
//    ));

    if ((int)err.code()) {
        emit laodScheduleErrorEvent(err.message());
        return;
    }

    emit loadScheduleSuccessEvent();
}
