#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "baseservice.h"
#include "domain/entity/user.h"

class UserService : public BaseService
{
    Q_OBJECT
public:
    explicit UserService(QObject* parent = nullptr, Repository* repository = QInjection::Inject)
        : BaseService(parent, repository) {}

    User loadUser();

    bool login(const QString& username, const QString& password);
};

#endif  // USERSERVICE_H
