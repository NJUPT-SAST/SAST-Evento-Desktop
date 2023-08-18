#include "evento_edit_helper.h"
#include "evento_edit.h"

EventoEditHelper *EventoEditHelper::getInstance()
{
    static EventoEditHelper instance;
    return &instance;
}

EventoEditHelper *EventoEditHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return getInstance();
}

/*--------------------------------------/
/                                       /
/                                       /
/    Waiting for the completed part     /
/                                       /
/                                       /
/--------------------------------------*/
