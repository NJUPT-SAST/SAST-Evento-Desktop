#ifndef EVENTOSCHEDULE_H
#define EVENTOSCHEDULE_H

#include <QObject>

class EventoBriefModel;

class EventoSchedule
{
    Q_OBJECT

public:
    using EventoID = QString;
    EventoSchedule();
public slots:
    void onClickEvento(EventoID);
    void onCheck(EventoID);
    void onFeedback(EventoID);
private:
    EventoBriefModel* m_eventoBriefModel;
};

#endif // EVENTOSCHEDULE_H
