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
    virtual QFuture<EventoResult<std::vector<DTO_Slide>>> getEventSlideList(EventoID id) override {
        return client.getEventSlideList(id);
    }
    virtual QFuture<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(const int size) override {
        return client.getHomeSlideList(size);
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
    virtual QFuture<EventoResult<bool>> subscribeEvent(EventoID event, bool selection) override {
        return client.subscribeEvent(event, selection);
    }
    virtual QFuture<EventoResult<bool>> registerEvent(EventoID event, bool selection) override {
        return client.registerEvent(event, selection);
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
    virtual QFuture<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId) override {
        return client.getFeedbackList(eventoId);
    }
    virtual QFuture<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId) override {
        return client.getFeedbackSummary(eventoId);
    }
    virtual QFuture<EventoResult<std::pair<int,std::vector<FeedbackNum>>>> getFeedbackSummaryListInPage(int page) override {
        return client.getFeedbackSummaryListInPage(page);
    }
    virtual QFuture<EventoResult<bool>> feedbackEvent(const DTO_Feedback& feedback) override {
        return client.feedbackEvent(feedback);
    }
    virtual QFuture<EventoResult<int>> hasFeedbacked(EventoID event) override {
        return client.hasFeedbacked(event);
    }
    virtual QFuture<EventoResult<DTO_Feedback>> getFeedbackInfo(EventoID event) override {
        return client.getFeedbackInfo(event);
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
