#include "department.h"

Department::Department(QString name, QString departmentId)
    : m_name(std::move(name)), m_departmentId(std::move(departmentId))
{}
