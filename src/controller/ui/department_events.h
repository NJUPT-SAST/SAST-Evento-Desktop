#ifndef DEPARTMENT_EVENTS_H
#define DEPARTMENT_EVENTS_H

#include <QtQml>

class DepartmentEventsController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DepartmentEventsController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadDepartmentsInfo();
    Q_INVOKABLE void loadSubscribedDepartment();
    Q_INVOKABLE void loadDepartmentEvents(int departmentId);
    Q_INVOKABLE void subscribeDepartment(bool isSubscribe, int departmentId);

signals:
    void loadSubscribedDepartmentsSuccessEvent(QString departmentJson);
    void loadSubscribedDepartmentsErrorEvent(QString message);
    void loadDepartmentsSuccessEvent(QString departmentJson);
    void loadDepartmentsErrorEvent(QString message);
    void loadDepartmentEventSuccessEvent();
    void loadDepartmentEventErrorEvent(QString message);
    void subscribeSuccessEvent();
    void subscribeErrorEvent(QString message);

private:
    DepartmentEventsController() = default;
public:
    void onLoadDepartmentsInfoFinished(const QString& departmentJson) {
        emit loadDepartmentsSuccessEvent(departmentJson);
    }
    void onLoadDepartmentsFailure(const QString& msg) {
        emit loadDepartmentsErrorEvent(msg);
    }
    void onLoadSubscribedDepartmentsFinished(const QString& departmentJson) {
        emit loadSubscribedDepartmentsSuccessEvent(departmentJson);
    }
    void onLoadSubscribedDepartmentsFailure(const QString& msg) {
        emit loadSubscribedDepartmentsErrorEvent(msg);
    }
    void onLoadDepartmentEventFinished() {
        emit loadDepartmentEventSuccessEvent();
    }
    void onLoadDepartmentEventFailure(const QString& msg) {
        emit loadDepartmentEventErrorEvent(msg);
    }
    void onSubscribeFinished() {
        emit subscribeSuccessEvent();
    }
    void onSubscribeFailure(const QString& msg) {
        emit subscribeErrorEvent(msg);
    }

    static DepartmentEventsController *getInstance();
    static DepartmentEventsController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // DEPARTMENT_EVENTS_H
