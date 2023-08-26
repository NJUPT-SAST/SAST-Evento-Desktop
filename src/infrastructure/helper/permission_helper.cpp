#include "permission_helper.h"

PermissionHelper *PermissionHelper::getInstance()
{
    static PermissionHelper instance;
    return &instance;
}

PermissionHelper *PermissionHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void PermissionHelper::updatePermission(const QString &permissionJson)
{
    setProperty("permissionJson", permissionJson);
//    setProperty("isEdited", true);
//    if (evento.id == 0)
//    {
//        setProperty("isEdited", false);
//        return;
//    }
}
