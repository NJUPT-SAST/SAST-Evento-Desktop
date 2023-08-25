#include "department_events.h"
#include "repository.h"
#include "convertor.h"
#include "evento_brief_model.h"

QString DepartmentEventsController::loadDepartmentsInfo()
{
    EventoException err;
    auto departmentList = getRepo()->get_department_list(err);
    if ((int)err.code()){
        emit loadDepartmentsErrorEvent(err.message());
        return QString();
    }
    emit loadDepartmentsSuccessEvent();
    return departmentList;
}

QString DepartmentEventsController::loadSubscribedDepartment()
{
    emit loadSubscribedDepartmentsSuccessEvent();
    return "[1]";
}

void DepartmentEventsController::loadDepartmentEvents(int departmentId)
{
    EventoException err;
    EventoBriefModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<EventoBrief>>()(
            getRepo()->get_department_event_list(departmentId, err)));

    if ((int)err.code()) {
        emit loadDepartmentEventErrorEvent(err.message());
        return;
    }

    emit loadDepartmentEventSuccessEvent();
}

void DepartmentEventsController::subscribeDepartment(bool check, int departmentId)
{
    emit subscribeSuccessEvent(check, departmentId);
}

DepartmentEventsController *DepartmentEventsController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new DepartmentEventsController();
}
