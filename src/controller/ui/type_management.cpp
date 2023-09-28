#include "type_management.h"

// deprecated

QString TypeManagementController::loadAllType() {
    emit loadAllTypeSuccess();
    return {};
}

void TypeManagementController::deleteType(const int typeId) {
    // TODO 删除类型请求操作
    return emit deleteTypeSuccess();
}

void TypeManagementController::changeTypeName(int id, const QString name) {
    // TODO 更改类型名操作
    return emit changeTypeNameSuccess();
}

void TypeManagementController::addType(const QString name) {
    // TODO 添加类型名操作
    return emit addTypeSuccess();
}

TypeManagementController* TypeManagementController::create(QQmlEngine* qmlEngine,
                                                           QJSEngine* jsEngine) {
    return new TypeManagementController();
}
