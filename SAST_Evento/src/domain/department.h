#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QString>

class Department
{
public:
    Department(QString name, QString departmentId);
private:
    QString m_name;
    QString m_departmentId;
};

#endif // DEPARTMENT_H
