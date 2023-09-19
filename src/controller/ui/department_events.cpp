#include "department_events.h"
#include "repository.h"
#include "evento_brief_model.h"
#include "evento_service.h"

void DepartmentEventsController::loadDepartmentsInfo()
{
    EventoException err;
    auto departmentList = getRepo()->getDepartmentList(err);
    if (err)
        return emit loadDepartmentsErrorEvent(err.message());
    emit loadDepartmentsSuccessEvent(departmentList);
}

void DepartmentEventsController::loadSubscribedDepartment()
{
    emit loadSubscribedDepartmentsSuccessEvent("[1]");
}

void DepartmentEventsController::loadDepartmentEvents(int departmentId)
{
//    auto future = getRepo()->getDepartmentEventList(departmentId);
//    future.waitForFinished();
//    auto result = future.takeResult();
//    if (!result) {
//        emit loadDepartmentEventErrorEvent(result.message());
//        return;
//    }
//    EventoBriefModel::getInstance()->resetModel(
//        Convertor<std::vector<DTO_Evento>, std::vector<EventoBrief>>()(result.take()));

    emit loadDepartmentEventSuccessEvent();
}

void DepartmentEventsController::subscribeDepartment(bool check, int departmentId)
{
    emit subscribeSuccessEvent();
}

DepartmentEventsController *DepartmentEventsController::getInstance()
{
    static DepartmentEventsController instance;
    return &instance;
}

DepartmentEventsController *DepartmentEventsController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
