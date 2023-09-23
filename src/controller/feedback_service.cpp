#include <QtConcurrent>

#include "feedback_service.h"
#include "repository.h"

#include "feedback_statistics.h"
#include "feedback_summary.h"
#include "feedback.h"

#include "feedback_summary_model.h"
#include "feedback_model.h"
#include "feedback_helper.h"
#include "feedback_statistics_helper.h"
#include "evento_info.h"


FeedbackSummary::FeedbackSummary(const std::pair<int,int>& feedbackCount):eventId(feedbackCount.first),
                                                                          feedbackNum(feedbackCount.second),
                                                                          subscribedNum(-1),
                                                                          registeredNum(-1),
                                                                          checkedNum(-1),
                                                                          aveScore(QString())
{
    title = QString("test");
    //title = undefined_function(feedbackCount.first)
    //获取名字
}

FeedbackSummary::FeedbackSummary(const DTO_FeedbackSummary& feedbackSummary):eventId(feedbackSummary.eventId),
                                                            feedbackNum(feedbackSummary.feedbacks.size()),
                                                            subscribedNum(feedbackSummary.subscribedNum),
                                                            registeredNum(feedbackSummary.registeredNum),
                                                            checkedNum(feedbackSummary.checkedNum),
                                                            aveScore(feedbackSummary.aveScore){
    title = QString("test");
    //title = undefined_function(feedbackSummary.first)
    //获取名字
}

Feedback::Feedback(const DTO_Feedback& feedback):id(feedback.id),eventId(feedback.eventId),score(feedback.score),content(feedback.content){}


void FeedbackService::load_UserFeedback(EventoID id) {
    EventoException err;
    getRepo()->getFeedbackInfo(id,err).then([=](EventoResult<DTO_Feedback> result) {
        if (!result)
            EventoInfoController::getInstance()->onLoadFailure(result.message());
        Feedback userfeedback;
        mutex.lock();
        auto feedback = result.take();
        std::lock_guard lock(mutex);
        userfeedback = std::move(feedback);
        mutex.unlock();
        FeedbackHelper::getInstance()->updateFeedback(userfeedback);
    });
}

void FeedbackService::load_SummaryInfo(int page) {
    getRepo()->getFeedbackSummaryListInPage(page).then([=](EventoResult<std::pair<int,std::vector<std::pair<int,int>>>> result) {
        if (!result)
            FeedbackStatisticsController::getInstance()->onLoadSummaryFailure(result.message());
        std::vector<FeedbackSummary> feedbackInfoList;
        mutex.lock();
        auto feedbackList = result.take();
        std::lock_guard lock(mutex);
        auto feedbackCountList = feedbackList.second;
        for(auto i:feedbackCountList){
            FeedbackSummary feedbackCount = i;
            feedbackInfoList.push_back(std::move(feedbackCount));
        }
        mutex.unlock();
        FeedbackSummaryModel::getInstance()->resetModel(feedbackInfoList);
        FeedbackStatisticsController::getInstance()->onLoadSummaryFinished(feedbackList.first);
    });
}


void FeedbackService::load_FeedbackInfo(EventoID id) {
    getRepo()->getFeedbackSummary(id).then([=](EventoResult<DTO_FeedbackSummary> result) {
        if (!result)
            FeedbackStatisticsController::getInstance()->onLoadFeedbackFailure(result.message());
        FeedbackSummary feedbackInfo;
        std::vector<Feedback> feedbacks;
        mutex.lock();
        auto feedbackSummary = result.take();
        std::lock_guard lock(mutex);
        for(auto i:feedbackSummary.feedbacks){
           feedbacks.push_back(i);
        };
        feedbackInfo = std::move(feedbackSummary);
        mutex.unlock();
        FeedbackModel::getInstance()->resetModel(feedbacks);
        FeedbackStatisticsHelper::getInstance()->updateFeedbackStatistics(feedbackInfo);
        FeedbackStatisticsController::getInstance()->onLoadFeedbackFinished();
    });
}

