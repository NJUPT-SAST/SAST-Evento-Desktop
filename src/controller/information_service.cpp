#include "information_service.h"
#include "department_events.h"
#include "department_model.h"
#include "evento_edit.h"
#include "evento_helper.h"
#include "evento_service.h"
#include "location_model.h"
#include "repository.h"
#include "type_model.h"

void InformationService::load_EditInfo(bool isEditMode) {
    DepartmentEventsController::getInstance();
    std::array<EventoPromise<bool>, 3> tasks = {
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
                DepartmentEventsController::getInstance()->onLoadDepartmentsFailure(
                    result.message());
                return false;
            }
            DepartmentModel::getInstance()->resetModel(result.take());
            DepartmentEventsController::getInstance()->onLoadDepartmentsFinished();
            return true;
        })};

    EventoPromise<bool>::all(tasks.begin(), tasks.end()).then([=](std::vector<bool> jobs) {
        for (auto i : jobs)
            if (!i)
                return;
        if (isEditMode)
            EventoEditController::getInstance()->setProperty(
                "index", TypeModel::getInstance()->getIndex(
                             EventoService::getInstance()
                                 .edit(EventoHelper::getInstance()->property("id").toInt())
                                 .type.id));
        EventoEditController::getInstance()->onLoadEditFinished();
    });
}

void InformationService::load_DepartmentInfo() {
    DepartmentEventsController::getInstance();
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

EventoPromise<EventTypeID> InformationService::getByDep(int dep) {
    if (dep_type_id[dep] != -1)
        return EventoPromise<EventTypeID>::resolve(dep_type_id[dep]);
    return getRepo()
        ->getTypeList()
        .then([this](EventoResult<std::vector<EventType>> result) {
            if (!result)
                return;
            auto type_list = result.take();
            for (const auto& i : type_list)
                if (i.name == "软研授课")
                    dep_type_id[0] = i.id;
            TypeModel::getInstance()->resetModel(std::move(type_list));
        })
        .then([=]() { return dep_type_id[dep]; });
}
