#ifndef DEPARTMENT_EVENTS_H
#define DEPARTMENT_EVENTS_H

#include <QtQml>

class DepartmentEventsController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DepartmentEventsController)
    QML_SINGLETON

public:
    Q_INVOKABLE QString loadDepartmentsInfo();
    Q_INVOKABLE void loadDepartmentEvents(int departmentId);

signals:
    void loadDepartmentsSuccessEvent();
    void loadDepartmentsErrorEvent(const QString &message);
    void loadDepartmentEventSuccessEvent();
    void loadDepartmentEventErrorEvent(const QString &message);

public:
    static DepartmentEventsController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    DepartmentEventsController() = default;
};

#endif // DEPARTMENT_EVENTS_H
