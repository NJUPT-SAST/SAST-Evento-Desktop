#include "evento_edit_helper.h"
#include "evento_edit.h"

EventoEditHelper *EventoEditHelper::getInstance()
{
    static EventoEditHelper instance;
    return &instance;
}

EventoEditHelper *EventoEditHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

/*--------------------------------------/
/                                       /
/                                       /
/    Waiting for the completed part     /
/                                       /
/                                       /
/--------------------------------------*/
