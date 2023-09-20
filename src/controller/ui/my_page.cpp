#include "my_page.h"
#include "evento_service.h"

void MyPageController::loadMyPageInfo() {
    EventoService::getInstance().load_History();
}

MyPageController *MyPageController::getInstance() {
    static MyPageController instance;
    return &instance;
}

MyPageController *MyPageController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
