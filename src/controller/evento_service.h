#ifndef EVENTO_SERVICE_H
#define EVENTO_SERVICE_H

#include <dto/evento.h>

class EventoService {
    std::vector<int> undertaking;
private:
    EventoService() = default;
public:
    static EventoService& getInstance() {
        static EventoService singleton;
        return singleton;
    }
};

#endif //EVENTO_SERVICE_H
