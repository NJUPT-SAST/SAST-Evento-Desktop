#include "evento_info.h"
#include "convertor.h"
#include "evento_exception.h"
#include "evento_helper.h"
#include "feedback_helper.h"
#include "slide_model.h"

void EventoInfoController::loadEventoInfo(const EventoID eventId)
{
    EventoException err;
//    EventoHelper::getInstance()->updateEvento(
//        Convertor<DTO_Evento, Evento>()(
//             getRepo()->get_event(eventId, err)),
//    );

    if ((int)err.code())
    {
        emit loadEventoErrorEvent(err.message());
        return;
    }

//    FeedbackHelper::getInstance()->updateFeedback(
//        Convertor<DTO_Feedback, Feedback>()(
//            getRepo()
//    ));

    if ((int)err.code())
    {
        emit loadEventoErrorEvent(err.message());
        return;
    }

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

EventoInfoController *EventoInfoController::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

EventoInfoController *EventoInfoController::getInstance()
{
    static EventoInfoController singleton;
    return &singleton;
}
