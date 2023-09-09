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

void DepartmentManagementController::deleteDepartment(const int departmentId)
{
    // TODO 删除部门操作
    return emit deleteDepartmentSuccess();
}

void DepartmentManagementController::changeDepartmentName(int id, const QString name)
{
    // TODO 更改部门操作
    return emit changeDepartmentNameSuccess();
}

void DepartmentManagementController::addDepartment(const QString name)
{
    // TODO 添加部门操作
    return emit addDepartmentSuccess();
}
