#include <QtConcurrent>

#include "feedback_service.h"
#include "repository.h"

#include "feedback_statistics.h"
#include "feedback_summary.h"

#include "feedback_num_model.h"
#include "feedback_model.h"
#include "feedback_helper.h"
#include "feedback_statistics_helper.h"
#include "evento_info.h"

void FeedbackService::load_UserFeedback(EventoID id) {
    getRepo()->getFeedbackInfo(id).then([=](EventoResult<DTO_Feedback> result) {
        if (!result) {
            EventoInfoController::getInstance()->onLoadFailure(result.message());
            return;
        }
        auto feedback = result.take();
        {
            std::lock_guard lock(mutex);
            userfeedback = std::move(feedback);
        }
        FeedbackHelper::getInstance()->updateFeedback(userfeedback);
    });
}

void FeedbackService::load_SummaryInfo(int page) {
    auto future = getRepo()->getFeedbackSummaryListInPage(page).then([=](EventoResult<std::pair<int, std::vector<FeedbackNum>>> result) {
        if (!result) {
            FeedbackStatisticsController::getInstance()->onLoadSummaryFailure(result.message());
            return -1;
        }
        auto data = result.take();
        std::vector<FeedbackNum> model;
        {
            std::lock_guard lock(mutex);
            for (const auto& i : data.second) {
                auto eventoFuture = getRepo()->getEventById(i.eventId).then([=](EventoResult<DTO_Evento> result) ->EventoResult<QString>{
                    if (!result) {
                        FeedbackStatisticsController::getInstance()->onLoadSummaryFailure(result.message());
                        return {result.code(), result.message()};
                    }
                    return result.take().title;
                });
                auto evento = eventoFuture.takeResult();
                if (!evento) {
                    FeedbackStatisticsController::getInstance()->onLoadSummaryFailure(result.message());
                    return -1;
                }
                FeedbackNum obj(i);
                obj.title = evento.take();
                model.push_back(obj);
            }
        }
        FeedbackNumModel::getInstance()->resetModel(std::move(model));
        return data.first;
    });
    QtConcurrent::run([=] {
        auto total = future.result();
        if (total != -1)
            FeedbackStatisticsController::getInstance()->onLoadSummaryFinished(total);
    });
}

void FeedbackService::load_FeedbackInfo(EventoID id) {
    auto future = getRepo()->getFeedbackSummary(id).then([=](EventoResult<DTO_FeedbackSummary> result) {
        if (!result) {
            FeedbackStatisticsController::getInstance()->onLoadFeedbackFailure(result.message());
            return false;
        }
        auto feedbackSummary = result.take();
        std::vector<Feedback> model;
        {
            std::lock_guard lock(mutex);
            for (auto& i : feedbackSummary.feedbacks) {
                model.push_back(Feedback(i));
                feedbacks[i.id] = Feedback(i);
            }
        }
        auto eventoFuture = getRepo()->getEventById(feedbackSummary.eventId).then([=](EventoResult<DTO_Evento> result) -> EventoResult<QString>{
            if (!result) {
                FeedbackStatisticsController::getInstance()->onLoadFeedbackFailure(result.message());
                return {result.code(), result.message()};
            }
            return result.take().title;
        });
        FeedbackModel::getInstance()->resetModel(std::move(model));
        auto evento = eventoFuture.takeResult();
        if (!evento) {
            FeedbackStatisticsController::getInstance()->onLoadFeedbackFailure(evento.message());
            return false;
        }
        FeedbackStatisticsHelper::getInstance()->updateFeedbackStatistics(FeedbackSummary(feedbackSummary, evento.take()));
        return true;
    });
    QtConcurrent::run([=] {
        if (future.result())
            FeedbackStatisticsController::getInstance()->onLoadFeedbackFinished();
    });
}

FeedbackSummary::FeedbackSummary(const DTO_FeedbackSummary& feedbackSummary, const QString& title):
    eventId(feedbackSummary.eventId),
    subscribedNum(feedbackSummary.subscribedNum),
    registeredNum(feedbackSummary.registeredNum),
    checkedNum(feedbackSummary.checkedNum),
    aveScore(feedbackSummary.aveScore),
    title(title)
{}

Feedback::Feedback(const DTO_Feedback& feedback):id(feedback.id),eventId(feedback.eventId),score(feedback.score),content(feedback.content){}

