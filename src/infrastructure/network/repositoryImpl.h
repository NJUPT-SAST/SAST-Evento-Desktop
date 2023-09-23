#ifndef REPOSITORY_IMPL_H
#define REPOSITORY_IMPL_H

#include <local/repositoryimpl.h>
#include "EventoNetworkClient.h"

class NetworkRepository : public repositoryImpl {
    EventoNetworkClient client;
public:
    virtual QFuture<EventoResult<QStringList>> getAdminPermission() override {
        return client.getAdminPermission();
    }
    virtual QFuture<EventoResult<QStringList>> getManagerPermission(EventoID event) override {
        return client.getManagerPermission(event);
    }
    virtual QFuture<EventoResult<QStringList>> getPermittedEvent() override {
        return client.getPermittedEvent();
    }
    virtual QFuture<EventoResult<DTO_Permission>> getEventPermission(EventoID event) override {
        return client.getEventPermission(event);
    }
    virtual QFuture<EventoResult<DTO_User>> getUserInfo(const UserID &id) override {
        return client.getUserInfo(id);
    }
    virtual QFuture<EventoResult<ParticipationStatus>> getUserParticipate(EventoID event) override {
        return client.getUserParticipate(event);
    }
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
    virtual QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event) override {
        return client.getEvent(event);
    }
    virtual QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code) override {
        return client.checkInEvent(event, code);
    }
    virtual QFuture<EventoResult<bool>> subscribeEvent(EventoID event, bool selection) override {
        return client.subscribeEvent(event, selection);
    }
    virtual QFuture<EventoResult<bool>> registerEvent(EventoID event, bool selection) override {
        return client.registerEvent(event, selection);
    }
    virtual QFuture<EventoResult<bool>> hasFeedbacked(EventoID event) override {
        return client.hasFeedbacked(event);
    }
    virtual QFuture<EventoResult<bool>> deleteEvent(EventoID event) override {
        return client.deleteEvent(event);
    }
    virtual QFuture<EventoResult<bool>> cancelEvent(EventoID event) override {
        return client.cancelEvent(event);
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
