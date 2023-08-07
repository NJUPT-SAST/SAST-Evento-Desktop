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
    explicit UserService(QObject* parent = nullptr, Repository* repository = QInjection::Inject):_repository(repository){};

    void login(const QString& code);

    Q_SIGNAL void loginSuccess();

private:
    Repository* _repository;
};

#endif  // USERSERVICE_H
