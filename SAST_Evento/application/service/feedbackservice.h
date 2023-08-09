#ifndef FEEDBACKSERVICE_H
#define FEEDBACKSERVICE_H

#include "baseservice.h"

class FeedbackService : public BaseService
{
    Q_OBJECT
public:
    explicit FeedbackService(QObject *parent = nullptr, Repository* repository = QInjection::Inject)
        : BaseService(parent, repository) {}

    Feedback loadFeedback(int eventId);

    std::vector<Feedback> loadFeedbackModel(int eventId);
};

#endif // FEEDBACKSERVICE_H
