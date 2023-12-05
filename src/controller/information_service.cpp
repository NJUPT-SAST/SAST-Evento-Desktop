#include "information_service.h"
#include "department_events.h"
#include "department_model.h"
#include "evento_edit.h"
#include "repository.h"
#include "type_model.h"

void InformationService::load_EditInfo() {
    std::array<QFuture<bool>, 3> tasks = {
        getRepo()->getTypeList().then([](EventoResult<std::vector<EventType>> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            auto typeList = result.take();
            TypeModel::getInstance()->resetModel(std::move(typeList));
            return true;
        }),
        getRepo()->getLocationList().then([this](EventoResult<QString> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            auto locationList = result.take();
            if (locationList.isEmpty())
                locationList = "[]";
            {
                std::lock_guard lock(mutex);
                EventoEditController::getInstance()->setProperty("locationJson", locationList);
                locationJson = std::move(locationList);
            }
            return true;
        }),
        getRepo()->getDepartmentList().then([this](EventoResult<std::vector<Department>> result) {
            if (!result) {
                DepartmentEventsController::getInstance()->onLoadDepartmentsFailure(
                    result.message());
                return false;
            }
            auto departmentList = result.take();
            DepartmentModel::getInstance()->resetModel(std::move(departmentList));
            DepartmentEventsController::getInstance()->onLoadDepartmentsFinished();
            return true;
        })};

    QtFuture::whenAll(tasks.begin(), tasks.end()).then([](QList<QFuture<bool>> tasks) {
        for (const auto& i : tasks)
            if (i.isCanceled() || !i.result())
                return;
        EventoEditController::getInstance()->onLoadEditFinished();
    });
}

void InformationService::load_DepartmentInfo() {
    getRepo()->getDepartmentListWithSubscriptionInfo().then(
        [this](EventoResult<std::vector<Department>> result) {
            if (!result) {
                DepartmentEventsController::getInstance()->onLoadDepartmentsFailure(
                    result.message());
                return;
            }
            auto departmentList = result.take();
            DepartmentModel::getInstance()->resetModel(std::move(departmentList));
            DepartmentEventsController::getInstance()->onLoadDepartmentsFinished();
        });
}

void InformationService::load_SubscribedDepartmentInfo() {
    getRepo()->getDepartmentListWithSubscriptionInfo().then(
        [this](EventoResult<std::vector<Department>> result) {
            if (!result) {
                DepartmentEventsController::getInstance()->onLoadDepartmentsFailure(
                    result.message());
                return;
            }
            auto departmentList = result.take();
            DepartmentModel::getInstance()->resetModel(std::move(departmentList));
            DepartmentEventsController::getInstance()->onLoadDepartmentsFinished();
        });
}
