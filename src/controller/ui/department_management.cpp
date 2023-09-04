#include "department_management.h"
#include "repository.h"

QString DepartmentManagementController::loadAllDepartment()
{
    EventoException err;
    QString res = getRepo()->get_department_list(err);
    if((int)err.code()) {
        emit loadAllDepartmentError(err.message());
        return QString();
    }
    emit loadAllDepartmentSuccess();
    return res;
}

void DepartmentManagementController::deleteDepartment(const int typeId)
{
    return emit deleteDepartmentSuccess();
}

void DepartmentManagementController::changeDepartmentName(int id, const QString name)
{
    return emit changeDepartmentNameSuccess();
}

void DepartmentManagementController::addDepartment(const QString name)
{
    return emit addDepartmentSuccess();
}
