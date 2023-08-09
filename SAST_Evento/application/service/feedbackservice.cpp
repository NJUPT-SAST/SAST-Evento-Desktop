#include "feedbackservice.h"

Feedback FeedbackService::loadFeedback(int eventId)
{
    return m_repository->feedback(eventId);
}

std::vector<Feedback> FeedbackService::loadFeedbackModel(int eventId)
{
    return m_repository->feedbackModel(eventId);
}
