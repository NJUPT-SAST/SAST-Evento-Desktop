#include "my_page.h"
#include "repository.h"

void MyPageController::loadMyPageInfo()
{
    auto future = getRepo()->getHistoryList();
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result)
        return emit loadMyPageErrorEvent(result.message());

    emit loadMyPageSuccessEvent();
}

MyPageController *MyPageController::getInstance()
{
    static MyPageController instance;
    return &instance;
}

MyPageController *MyPageController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
