#include "location_management.h"
#include "repository.h"

// deprecated

QString LocationManagementController::loadAllLocation()
{
    EventoException err;
    QString res = getRepo()->getLocationList(err);
    if((int)err.code()) {
        emit loadAllLocationError(err.message());
        return QString();
    }
    emit loadAllLocationSuccess();
    return res;
}

void LocationManagementController::deleteLocation(const int locationId)
{
    // TODO 删除地点操作
    return emit deleteTLocationSuccess();
}

void LocationManagementController::changeLocationName(int id, const QString name)
{
    // TODO 更改地点操作（谨慎使用）
    return emit changeLocationNameSuccess();
}

void LocationManagementController::addLocation(const QString name, const int parentId)
{
    // TODO 添加地点操作
    return emit addLocationSuccess();
}
