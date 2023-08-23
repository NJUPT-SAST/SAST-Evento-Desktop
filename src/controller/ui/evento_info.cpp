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
            getRepo()->get_event_slide_list(eventId, err)
    ));
    if ((int)err.code())
        return emit loadEventoErrorEvent(err.message());

    auto event = getRepo()->get_event(eventId, err);
    if ((int)err.code())
        return emit loadEventoErrorEvent(err.message());
    auto participate = getRepo()->get_user_participate(eventId, err);
    if ((int)err.code())
        return emit loadEventoErrorEvent(err.message());

    EventoHelper::getInstance()->updateEvento(
        Convertor<DTO_Evento, Evento>()(event),
        participate
    );

    FeedbackHelper::getInstance()->updateFeedback(
        Convertor<DTO_Feedback, Feedback>()(
            getRepo()->get_feedback_info(eventId, err)
    ));
    if ((int)err.code())
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
