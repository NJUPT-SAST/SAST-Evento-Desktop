#ifndef EVENTO_SERVICE_H
#define EVENTO_SERVICE_H

#include <dto/evento.h>

#include <QFuture>
#include <shared_mutex>

class EventoService {
    std::shared_mutex mutex;

    std::vector<EventoID> undertaking;
    std::vector<EventoID> latest;
    std::vector<EventoID> registered;
    std::vector<EventoID> subscribed;
    std::vector<EventoID> departmentEvento;
    std::vector<EventoID> history;
    std::vector<EventoID> blocks;
    std::map<EventoID, DTO_Evento> stored;
private:
    EventoService() = default;
public:
    static EventoService& getInstance() {
        static EventoService singleton;
        return singleton;
    }

    void load_Plaza();
    void load_RegisteredSchedule();
    void load_SubscribedSchedule();
    void load_DepartmentEvents(int departmentId);
    void load_History();
    void load_Block(const QString& time);
    void load(EventoID id);
    DTO_Evento edit(EventoID id);
    void create(const QString& title,
                 const QString& description,
                 const QString& eventStart,
                 const QString& eventEnd,
                 const QString& registerStart,
                 const QString& registerEnd,
                 int typeId, int locationId,
                 const QVariantList& departmentIds,
                 const QString& tag);
    void edit(EventoID id,
                const QString& title,
                const QString& description,
                const QString& eventStart,
                const QString& eventEnd,
                const QString& registerStart,
                const QString& registerEnd,
                int typeId, int locationId,
                const QVariantList& departmentIds,
                const QString& tag);
    void update(const DTO_Evento& event);
    void update(const std::vector<DTO_Evento>& events);
    void getQRCode(EventoID id);
    void del(EventoID id);
    void cancel(EventoID id);
};

#endif //EVENTO_SERVICE_H
