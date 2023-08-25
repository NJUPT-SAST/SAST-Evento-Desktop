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

public:
    static DepartmentEventsController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    DepartmentEventsController() = default;
};

#endif // DEPARTMENT_EVENTS_H
