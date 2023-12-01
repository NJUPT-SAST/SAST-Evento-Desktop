#include "calendar.h"
#include "evento_block_model.h"
#include "evento_service.h"

void CalendarController::loadAllEventoInfo(QString date) {
    EventoService::getInstance().load_Block(QDate::fromString(date, "yyyy-M-d"));
}

void CalendarController::loadEventoInfo(EventoID eventId) {
    EventoService::getInstance().load_Event(eventId);
}

void CalendarController::deleteEvento(EventoID eventId) {
    EventoService::getInstance().del(eventId);
}

void CalendarController::cancelEvento(EventoID eventId) {
    EventoService::getInstance().cancel(eventId);
}

void CalendarController::loadCheckCode(EventoID eventId) {
    EventoService::getInstance().getQRCode(eventId);
}

CalendarController::CalendarController() {
    EventoBlockModel::getInstance();
}

CalendarController* CalendarController::getInstance() {
    static CalendarController instance;
    return &instance;
}

CalendarController* CalendarController::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
