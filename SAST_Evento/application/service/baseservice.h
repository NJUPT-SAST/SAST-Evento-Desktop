#ifndef BASESERVICE_H
#define BASESERVICE_H

#include <QObject>
#include "domain/repository/repository.h"
#include <infrastructure/injection/dependencyinjector.h>

using namespace QInjection;

class BaseService : public QObject
{
    Q_OBJECT
public:
    explicit BaseService(QObject *parent = nullptr, Repository* repository = QInjection::Inject)
      : m_repository(repository) {}

protected:
    Repository* m_repository;
};

#endif  // BASESERVICE_H
