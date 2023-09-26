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
    auto future = getRepo()->getFeedbackInfo(id).then([=](EventoResult<DTO_Feedback> result) {
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
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
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
            for (auto& i : data.second) {
                model.push_back(i);
                feedbacks[i.eventId] = std::move(i);
            }
        }
        FeedbackNumModel::getInstance()->resetModel(std::move(model));
        return data.first;
    });
    QtConcurrent::run([=] {
        auto f(future);
        auto total = f.takeResult();
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
            }
        }
        FeedbackModel::getInstance()->resetModel(std::move(model));
        FeedbackStatisticsHelper::getInstance()->updateFeedbackStatistics(FeedbackSummary(feedbackSummary, feedbacks[id].title));
        return true;
    });
    QtConcurrent::run([=] {
        auto f(future);
        if (f.takeResult())
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

