#include "department_events.h"
#include "repository.h"

QString DepartmentEventsController::loadDepartmentsInfo()
{
    EventoException err;
    auto departmentList = getRepo()->get_department_list(err);
    if ((int)err.code()){
        return QString();
    }
    return departmentList;
}

DepartmentEventsController *DepartmentEventsController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new DepartmentEventsController();
}
