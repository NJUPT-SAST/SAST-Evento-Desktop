#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <QFuture>
#include <shared_mutex>
#include "types.h"

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
    void subscribeEvento(EventoID id, bool selection);
    void registerEvento(const EventoID id, bool selection);
    void load_EventoInfo(const EventoID eventId);

};

#endif // USER_SERVICE_H
