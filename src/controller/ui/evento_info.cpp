#include "evento_info.h"
#include "convertor.h"
#include "evento_exception.h"
#include "evento_helper.h"
#include "feedback_helper.h"
#include "slide_model.h"

void EventoInfoController::loadEventoInfo(const EventoID eventId)
{
    EventoException err;
    SlideModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(
            getRepo()->getEventSlideList(eventId, err)
    ));
    if (err)
        return emit loadEventoErrorEvent(err.message());

    auto future = getRepo()->getEventById(eventId);
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result)
        err = result;
    if (err)
        return emit loadEventoErrorEvent(err.message());
    auto participate = getRepo()->getUserParticipate(eventId, err);
    if (err)
        return emit loadEventoErrorEvent(err.message());

    auto event = result.take();
    EventoHelper::getInstance()->updateEvento(
        Convertor<DTO_Evento, Evento>()(event),
        participate
    );

    FeedbackHelper::getInstance()->updateFeedback(
        Convertor<DTO_Feedback, Feedback>()(
            getRepo()->getFeedbackInfo(eventId, err)
    ));
    if (err)
        return emit loadEventoErrorEvent(err.message());

    emit loadEventoSuccessEvent();
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

EventoInfoController *EventoInfoController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new EventoInfoController();
}
