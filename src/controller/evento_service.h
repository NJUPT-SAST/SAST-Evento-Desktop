#ifndef EVENTO_SERVICE_H
#define EVENTO_SERVICE_H

#include <dto/evento.h>

#include <QFuture>
#include <shared_mutex>

class EventoService {
    static constexpr int buffer_szie = 100;
    std::shared_mutex mutex;

    std::vector<EventoID> undertaking;
    std::vector<EventoID> latest;
    std::map<EventoID, DTO_Evento> stored;
private:
    EventoService() = default;
public:
    static EventoService& getInstance() {
        static EventoService singleton;
        return singleton;
    }

    void load_Plaza();
    void load(EventoID id);
    DTO_Evento edit(EventoID id);
    void update(const DTO_Evento& event);
    void update(const std::vector<DTO_Evento>& events);
};

#endif //EVENTO_SERVICE_H
