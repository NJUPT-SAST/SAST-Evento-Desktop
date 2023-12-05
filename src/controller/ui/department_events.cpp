#include "department_events.h"
#include "evento_service.h"
#include "information_service.h"

void DepartmentEventsController::loadDepartments() {
    InformationService::getInstance().load_DepartmentInfo();
}

void DepartmentEventsController::loadDepartmentsWithSubscriptionInfo() {
    InformationService::getInstance().load_SubscribedDepartmentInfo();
}

void DepartmentEventsController::loadDepartmentEvents(int departmentId) {
    EventoService::getInstance().load_DepartmentEvents(departmentId);
}

void DepartmentEventsController::subscribeDepartment(bool check, int departmentId) {
    EventoService::getInstance().subscribeDepartment(departmentId, check);
}

DepartmentEventsController* DepartmentEventsController::getInstance() {
    static DepartmentEventsController instance;
    return &instance;
}

DepartmentEventsController* DepartmentEventsController::create(QQmlEngine* qmlEngine,
                                                               QJSEngine* jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
