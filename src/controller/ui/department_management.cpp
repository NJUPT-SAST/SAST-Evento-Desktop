#include "department_management.h"

QString DepartmentManagementController::loadAllDepartment() {
    emit loadAllDepartmentSuccess();
    return {};
}

void DepartmentManagementController::deleteDepartment(const int departmentId) {
    // TODO 删除部门操作
    return emit deleteDepartmentSuccess();
}

void DepartmentManagementController::changeDepartmentName(int id, const QString name) {
    // TODO 更改部门操作
    return emit changeDepartmentNameSuccess();
}

void DepartmentManagementController::addDepartment(const QString name) {
    // TODO 添加部门操作
    return emit addDepartmentSuccess();
}
