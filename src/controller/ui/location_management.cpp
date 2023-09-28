#include "location_management.h"

// deprecated

QString LocationManagementController::loadAllLocation() {
    emit loadAllLocationSuccess();
    return {};
}

void LocationManagementController::deleteLocation(const int locationId) {
    // TODO 删除地点操作
    return emit deleteTLocationSuccess();
}

void LocationManagementController::changeLocationName(int id, const QString name) {
    // TODO 更改地点操作（谨慎使用）
    return emit changeLocationNameSuccess();
}

void LocationManagementController::addLocation(const QString name, const int parentId) {
    // TODO 添加地点操作
    return emit addLocationSuccess();
}
