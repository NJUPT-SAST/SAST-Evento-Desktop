#include "my_page.h"
#include "evento_exception.h"
#include "evento_brief_model.h"
#include "convertor.h"

void MyPageController::loadHistoryInfo()
{
    EventoException err;
    EventoBriefModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<EventoBrief> >()(
            getRepo()->get_history_list(err)
    ));

    if ((int)err.code())
        return emit loadHistoryErrorEvent(err.message());
    emit loadHistorySuccessEvent();
}

MyPageController *MyPageController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new MyPageController();
}
