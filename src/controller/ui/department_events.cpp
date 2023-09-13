#include "department_events.h"
#include "repository.h"
#include "convertor.h"
#include "evento_brief_model.h"

QString DepartmentEventsController::loadDepartmentsInfo()
{
    EventoException err;
    auto departmentList = getRepo()->getDepartmentList(err);
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
    auto future = getRepo()->getDepartmentEventList(departmentId);
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result) {
        emit loadDepartmentEventErrorEvent(result.message());
        return;
    }
    EventoBriefModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<EventoBrief>>()(result.take()));

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
