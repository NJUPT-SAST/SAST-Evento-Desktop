#include "evento_helper.h"
#include "evento.h"

EventoHelper* EventoHelper::getInstance() {
    static EventoHelper instance;
    return &instance;
}

EventoHelper* EventoHelper::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void EventoHelper::update(const Evento& evento) {
    setProperty("title", evento.title);
    setProperty("state", (int)evento.state);
    setProperty("eventTime", evento.eventTime);
    setProperty("registerTime", evento.registrationTime);
    setProperty("department", evento.department);
    setProperty("location", evento.location);
    setProperty("tag", evento.tag);
    setProperty("type", evento.type.name);
    setProperty("description", evento.description);
}
