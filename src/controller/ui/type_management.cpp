#include "type_management.h"
#include "repository.h"

QString TypeManagementController::loadAllType()
{
    EventoException err;
    QString res = getRepo()->get_type_list(err);
    if((int)err.code()) {
        emit loadAllTypeError(err.message());
        return QString();
    }
    emit loadAllTypeSuccess();
    return res;
}

void TypeManagementController::deleteType(const int typeId)
{
    // TODO 删除类型请求操作
    return emit deleteTypeSuccess();
}

void TypeManagementController::changeTypeName(int id, const QString name)
{
    // TODO 更改类型名操作
    return emit changeTypeNameSuccess();
}

void TypeManagementController::addType(const QString name)
{
    // TODO 添加类型名操作
    return emit addTypeSuccess();
}

TypeManagementController *TypeManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new TypeManagementController();
}
