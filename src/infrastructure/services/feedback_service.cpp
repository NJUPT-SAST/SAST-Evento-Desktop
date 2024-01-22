#include "feedback_service.h"

#include "evento_info.h"
#include "feedback_helper.h"
#include "feedback_model.h"
#include "feedback_num_model.h"
#include "feedback_statistics.h"
#include "feedback_statistics_helper.h"
#include "feedback_summary.h"
#include "repository.h"

void FeedbackService::load_UserFeedback(EventoID id) {
    FeedbackHelper::getInstance();
    getRepo()->getFeedbackInfo(id).then([](EventoResult<DTO_Feedback> result) {
        if (!result) {
            EventoInfoController::getInstance()->onLoadFailure(result.message());
            return;
        }
        auto feedback = result.take();
        FeedbackHelper::getInstance()->updateFeedback(Feedback(feedback));
    });
}

void FeedbackService::load_SummaryInfo(int page) {
    getRepo()->getFeedbackSummaryListInPage(page).then(
        [this](EventoResult<std::pair<int, std::vector<FeedbackNum>>> result) {
            if (!result) {
                FeedbackStatisticsController::getInstance()->onLoadSummaryFailure(result.message());
                return;
            }
            auto data = result.take();
            std::vector<FeedbackNum> model;
            {
                std::lock_guard lock(mutex);
                for (auto& i : data.second) {
                    i.title = i.title.trimmed();
                    model.push_back(i);
                    feedbacks[i.eventId] = std::move(i);
                }
            }
            FeedbackNumModel::getInstance()->resetModel(std::move(model));
            FeedbackStatisticsController::getInstance()->onLoadSummaryFinished(data.first);
        });
}

void FeedbackService::feedback(EventoID id, int score, const QString& content) {
    getRepo()
        ->feedbackEvent(DTO_Feedback{0, id, score, content})
        .then([](EventoResult<bool> result) {
            if (!result) {
                EventoInfoController::getInstance()->onFeedbackFailure(result.message());
                return;
            }
            EventoInfoController::getInstance()->onFeedbackFinished();
        });
}

void FeedbackService::load_FeedbackInfo(EventoID id) {
    getRepo()->getFeedbackSummary(id).then([=](EventoResult<DTO_FeedbackSummary> result) {
        if (!result) {
            FeedbackStatisticsController::getInstance()->onLoadFeedbackFailure(result.message());
            return;
        }
        auto feedbackSummary = result.take();
        std::vector<Feedback> model;
        {
            std::lock_guard lock(mutex);
            for (auto& i : feedbackSummary.feedbacks) {
                if (!i.content.isEmpty())
                    model.push_back(Feedback(i));
            }
        }
        FeedbackModel::getInstance()->resetModel(std::move(model));
        FeedbackStatisticsHelper::getInstance()->updateFeedbackStatistics(
            FeedbackSummary(feedbackSummary, feedbacks[id].title));
        FeedbackStatisticsController::getInstance()->onLoadFeedbackFinished();
    });
}

FeedbackSummary::FeedbackSummary(const DTO_FeedbackSummary& feedbackSummary, const QString& title)
    : eventId(feedbackSummary.eventId), subscribedNum(feedbackSummary.subscribedNum),
      registeredNum(feedbackSummary.registeredNum), checkedNum(feedbackSummary.checkedNum),
      aveScore(feedbackSummary.aveScore), title(title.trimmed()) {}

Feedback::Feedback(const DTO_Feedback& feedback)
    : id(feedback.id), eventId(feedback.eventId), score(feedback.score),
      content(feedback.content.trimmed()) {}
