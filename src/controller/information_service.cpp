#include "information_service.h"
#include "department_events.h"
#include "department_model.h"
#include "evento_edit.h"
#include "location_model.h"
#include "repository.h"
#include "type_model.h"

void InformationService::load_EditInfo() {
    std::array<QFuture<bool>, 3> tasks = {
        getRepo()->getTypeList().then([](EventoResult<std::vector<EventType>> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            TypeModel::getInstance()->resetModel(result.take());
            return true;
        }),
        getRepo()->getLocationList().then([this](EventoResult<std::vector<DTO_Location>> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            LocationModel::getInstance()->resetModel(result.take());
            return true;
        }),
        getRepo()->getDepartmentList().then([this](EventoResult<std::vector<Department>> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            DepartmentModel::getInstance()->resetModel(result.take());
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
