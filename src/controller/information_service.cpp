#include <QtConcurrent>
#include "information_service.h"
#include "repository.h"
#include "evento_edit.h"
#include "department_events.h"
#include "type_model.h"

void InformationService::load_EditInfo() {
    std::array<QFuture<bool>, 3> tasks {
        getRepo()->getTypeList().then([=](EventoResult<std::vector<EventType>> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            auto typeList = result.take();
            {
                std::lock_guard lock(mutex);
                TypeModel::getInstance()->resetModel(typeList);
                types = std::move(typeList);
            }
            return true;
        }),
        getRepo()->getLocationList().then([=](EventoResult<QString> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            auto locationList = result.take();
            if (locationList.isEmpty()) locationList = "[]";
            {
                std::lock_guard lock(mutex);
                EventoEditController::getInstance()->setProperty("locationJson", locationList);
                locationJson = std::move(locationList);
            }
            return true;
        }),
        getRepo()->getDepartmentList().then([=](EventoResult<QString> result) {
            if (!result) {
                EventoEditController::getInstance()->onLoadEditFailure(result.message());
                return false;
            }
            auto departmentList = result.take();
            if (departmentList.isEmpty()) departmentList = "[]";
            {
                std::lock_guard lock(mutex);
                EventoEditController::getInstance()->setProperty("departmentJson", departmentList);
                departmentJson = std::move(departmentList);
            }
            return true;
        })
    };
    auto t = QtConcurrent::run([=] {
        for (const auto& i : tasks)
            if (!i.result())
                return;
        EventoEditController::getInstance()->onLoadEditFinished();
    });
}

void InformationService::load_DepartmentInfo()
{
    auto future = getRepo()->getDepartmentList().then([=](EventoResult<QString> result) {
        if (!result) {
            DepartmentEventsController::getInstance()->onLoadDepartmentsFailure(result.message());
            return;
        }
        auto departmentList = result.take();
        if (departmentList.isEmpty()) departmentList = "[]";
        {
            std::lock_guard lock(mutex);
            departmentJson = std::move(departmentList);
        }
        DepartmentEventsController::getInstance()->onLoadDepartmentsInfoFinished(departmentJson);
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}

void InformationService::load_SubscribedDepartmentInfo()
{
    auto future = getRepo()->getSubscribedDepartmentList().then([=](EventoResult<QString> result) {
        if (!result) {
            DepartmentEventsController::getInstance()->onLoadSubscribedDepartmentsFailure(result.message());
            return;
        }
        auto departmentList = result.take();
        {
            std::lock_guard lock(mutex);
            subscribedDepartmentJson = std::move(departmentList);
        }
        DepartmentEventsController::getInstance()->onLoadSubscribedDepartmentsFinished(subscribedDepartmentJson);
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}
