#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include <infrastructure/injection/dependencyinjector.h>

#include "domain/repository/repository.h"
#include "baseservice.h"

using namespace QInjection;

class UserService : public BaseService
{
    Q_OBJECT
public:
    explicit UserService(QObject* parent = nullptr, Repository* repository = QInjection::Inject)
        : m_repository(repository) {};

    bool login(const QString& username, const QString& password);

private:
    Repository* m_repository;
};

#endif  // USERSERVICE_H
