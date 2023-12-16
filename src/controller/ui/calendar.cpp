#include "calendar.h"
#include "evento_block_model.h"
#include "evento_service.h"
#include "lesson_model.h"

void CalendarController::generateLessonPic(DepartmentEnum dep) {
    std::vector<EventoLesson> data;
    auto& test = data.emplace_back();
    test.departments.push_back("C++组");
    test.time = "周日 17：00";
    test.topic = "?";
    test.image = "qrc:/res/image/department/cpp_1.svg";
    {
        auto& test = data.emplace_back();
        test.departments.push_back("C++组");
        test.time = "周日 17：00";
        test.topic = "?";
        test.image = "qrc:/res/image/department/cpp_1.svg";
    }
    LessonModel::getInstance()->resetModel(std::move(data));
}

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
