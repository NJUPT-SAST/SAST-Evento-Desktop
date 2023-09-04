#ifndef DEPARTMENT_MANAGEMENT_H
#define DEPARTMENT_MANAGEMENT_H

#include <QtQml>

class DepartmentManagementController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DepartmentManagementController)
    QML_SINGLETON

public:
    Q_INVOKABLE QString loadAllDepartment();
    Q_INVOKABLE void deleteDepartment(const int typeId);
    Q_INVOKABLE void changeDepartmentName(int id, const QString name);
    Q_INVOKABLE void addDepartment(const QString name);

signals:
    void loadAllDepartmentSuccess();
    void loadAllDepartmentError(const QString &message);

    void deleteDepartmentSuccess();
    void deleteDepartmentError(const QString &message);

    void changeDepartmentNameSuccess();
    void changeDepartmentNameError(const QString &message);

    void addDepartmentSuccess();
    void addDepartmentError(const QString &message);

public:
    DepartmentManagementController() = default;
    static DepartmentManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // DEPARTMENT_MANAGEMENT_H
