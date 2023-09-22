#include "evento_info.h"
#include "repository.h"
#include "evento_service.h"
#include "evento_exception.h"
#include "feedback_helper.h"
#include "slide_model.h"

void EventoInfoController::loadEventoInfo(const EventoID eventId)
{
    EventoException err;
//    SlideModel::getInstance()->resetModel(
//        Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(
//            getRepo()->getEventSlideList(eventId, err)
//    ));
//    if (err)
//        return emit loadEventoErrorEvent(err.message());

    auto participate = getRepo()->getUserParticipate(eventId, err);
    if (err)
        return emit loadEventoErrorEvent(err.message());

    setProperty("isRegistrated", participate.isRegistrated);
    setProperty("isParticipated", participate.isParticipated);
    setProperty("isSubscribed", participate.isSubscribed);

//    FeedbackHelper::getInstance()->updateFeedback(
//        Convertor<DTO_Feedback, Feedback>()(
//            getRepo()->getFeedbackInfo(eventId, err)
//    ));
//    if (err)
//        return emit loadEventoErrorEvent(err.message());

    EventoService::getInstance().load(eventId);
    //此处不能删去上一行，feedbackservice在其中被调用
}

void EventoInfoController::registerEvento(const EventoID id, bool isParticipated)
{
    emit registerSuccessEvent();
}

void EventoInfoController::feedbackEvento(const QString &content, const int score, const EventoID id)
{
    emit feedbackSuccessEvent();
}

void EventoInfoController::subscribeEvento(const EventoID id, bool isParticipated)
{
    emit subscribeSuccessEvent();
}

EventoInfoController *EventoInfoController::getInstance()
{
    static EventoInfoController instance;
    return &instance;
}

EventoInfoController *EventoInfoController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}
