#ifndef REPOSITORY_IMPL_H
#define REPOSITORY_IMPL_H

#include <local/repositoryimpl.h>
#include "EventoNetworkClient.h"

class NetworkRepository : public repositoryImpl {
    EventoNetworkClient client;
public:
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList() override {
        return client.getUndertakingList();
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList() override {
        return client.getLatestList();
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList() override {
        return client.getRegisteredList();
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList() override {
        return client.getSubscribedList();
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList() override {
        return client.getHistoryList();
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size) override {
        return client.getEventList(page, size);
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId) override {
        return client.getDepartmentEventList(departmentId);
    }
    virtual QFuture<EventoResult<std::vector<EventType>>> getTypeList() override {
        return client.getTypeList();
    }
    virtual QFuture<EventoResult<QString>> getDepartmentList() override {
        return client.getDepartmentList();
    }
    virtual QFuture<EventoResult<QString>> getSubscribedDepartmentList() override {
        return client.getSubscribedDepartmentList();
    }
    virtual QFuture<EventoResult<QString>> getQRCode(EventoID eventId) override {
        return client.getQRCode(eventId);
    }
    virtual QFuture<EventoResult<QString>> getLocationList() override {
        return client.getLocationList();
    }
    virtual QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event) override {
        return client.getEvent(event);
    }
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListByTime(const QString& time) override {
        return client.getEventListByTime(time);
    }
    virtual QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code) override {
        return client.checkInEvent(event, code);
    }
    virtual QFuture<EventoResult<bool>> hasFeedbacked(EventoID event) override {
        return client.isFeedbacked(event);
    }
    virtual QFuture<EventoResult<bool>> deleteEvent(EventoID event) override {
        return client.deleteEvent(event);
    }
    virtual QFuture<EventoResult<bool>> cancelEvent(EventoID event) override {
        return client.cancelEvent(event);
    }
    virtual QFuture<EventoResult<bool>> createEvent(const QString& title,
                                                    const QString& description,
                                                    const QString& eventStart,
                                                    const QString& eventEnd,
                                                    const QString& registerStart,
                                                    const QString& registerEnd,
                                                    int typeId, int locationId,
                                                    const QVariantList& departmentIds,
                                                    const QString& tag) override {
        return client.createEvent(title, description, eventStart, eventEnd, registerStart, registerEnd, typeId, locationId, departmentIds, tag);
    }
    virtual QFuture<EventoResult<bool>> editEvent(EventoID event,
                                                  const QString& title,
                                                  const QString& description,
                                                  const QString& eventStart,
                                                  const QString& eventEnd,
                                                  const QString& registerStart,
                                                  const QString& registerEnd,
                                                  int typeId, int locationId,
                                                  const QVariantList& departmentIds,
                                                  const QString& tag) override {
        return client.editEvent(event, title, description, eventStart, eventEnd, registerStart, registerEnd, typeId, locationId, departmentIds, tag);
    }

private:
    NetworkRepository() = default;
public:
    static NetworkRepository* getInstance() {
        static NetworkRepository singleton;
        return &singleton;
    }
};

#endif // REPOSITORY_IMPL_H
