#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <QFuture>
#include <shared_mutex>

class UserService
{
private:
    UserService() = default;
public:
    static UserService& getInstance() {
        static UserService singleton;
        return singleton;
    }

    void checkIn(const int eventId, const QString &code);

};

#endif // USER_SERVICE_H
