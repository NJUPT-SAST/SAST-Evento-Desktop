#include "my_page.h"
#include "evento_brief_model.h"
#include "convertor.h"

void MyPageController::loadMyPageInfo()
{
    auto future = getRepo()->getHistoryList();
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result)
        return emit loadMyPageErrorEvent(result.message());
    EventoBriefModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<EventoBrief>>()(result.take()));

    emit loadMyPageSuccessEvent();
}

MyPageController *MyPageController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new MyPageController();
}
