#ifndef FEEDBACKSTATISTICSCONTROLLER_H
#define FEEDBACKSTATISTICSCONTROLLER_H

#include "basecontroller.h"
#include "application/service/eventservice.h"
#include "application/service/feedbackservice.h"

class FeedbackStatisticsController : public BaseController
{
    Q_OBJECT
    QML_NAMED_ELEMENT(FeedbackStatisticsController)

public:
    explicit FeedbackStatisticsController(QObject *parent = nullptr);

private:
    EventService* m_eventService() { return QInjection::Inject; }
    FeedbackService* m_feedbackService() { return QInjection::Inject; }
};

#endif // FEEDBACKSTATISTICSCONTROLLER_H
