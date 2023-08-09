#ifndef EVENTSERVICE_H
#define EVENTSERVICE_H

#include "baseservice.h"

class EventService : public BaseService
{
    Q_OBJECT

public:
    explicit EventService(QObject *parent = nullptr, Repository* repository = QInjection::Inject)
        : BaseService(parent, repository) {}

    Evento loadEvento(int eventId);

    Department loadDepartment();

    std::vector<UndertakingEvento> loadUndertakingEvento();
};

#endif // EVENTSERVICE_H
