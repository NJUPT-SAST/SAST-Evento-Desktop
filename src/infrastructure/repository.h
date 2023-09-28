#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "dto/evento.h"
#include "dto/feedback.h"
#include "dto/feedback_summary.h"
#include "dto/permission.h"
#include "dto/slide.h"
#include "dto/user.h"
#include "dto/user_brief.h"

#include "result.h"
#include "types.h"

#include <QFuture>

struct Repository {
    // user-fetch
    virtual QFuture<EventoResult<QStringList>> getAdminPermission() = 0;
    virtual QFuture<EventoResult<QStringList>> getManagerPermission(EventoID event) = 0;
    virtual QFuture<EventoResult<QStringList>> getPermittedEvent() = 0;
    virtual QFuture<EventoResult<DTO_Permission>> getEventPermission(EventoID event) = 0;
    virtual QFuture<EventoResult<DTO_User>> getUserInfo(const UserID& id) = 0;
    virtual QFuture<EventoResult<ParticipationStatus>> getUserParticipate(EventoID event) = 0;

    // event-fetch
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page,
                                                                              int size) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>>
        getDepartmentEventList(int departmentId) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>>
        getEventListByTime(const QString& time) = 0;
    virtual QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Slide>>> getEventSlideList(EventoID id) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(const int size) = 0;
    virtual QFuture<EventoResult<std::vector<EventType>>> getTypeList() = 0;
    virtual QFuture<EventoResult<QString>> getLocationList() = 0;
    virtual QFuture<EventoResult<QString>> getDepartmentList() = 0;
    virtual QFuture<EventoResult<QString>> getSubscribedDepartmentList() = 0;
    virtual QFuture<EventoResult<QString>> getQRCode(EventoID eventId) = 0;

    // event-upload
    virtual QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code) = 0;
    virtual QFuture<EventoResult<bool>> subscribeEvent(EventoID event, bool unsubscribe) = 0;
    virtual QFuture<EventoResult<bool>> registerEvent(EventoID event, bool unsubscribe) = 0;
    virtual QFuture<EventoResult<bool>> cancelEvent(EventoID event) = 0;
    virtual QFuture<EventoResult<bool>> deleteEvent(EventoID event) = 0;
    virtual QFuture<EventoResult<bool>>
        createEvent(const QString& title, const QString& description, const QString& eventStart,
                    const QString& eventEnd, const QString& registerStart,
                    const QString& registerEnd, int typeId, int locationId,
                    const QVariantList& departmentIds, const QString& tag) = 0;
    virtual QFuture<EventoResult<bool>>
        editEvent(EventoID event, const QString& title, const QString& description,
                  const QString& eventStart, const QString& eventEnd, const QString& registerStart,
                  const QString& registerEnd, int typeId, int locationId,
                  const QVariantList& departmentIds, const QString& tag) = 0;
    virtual QFuture<EventoResult<bool>> subscribeDepartment(int departmentId, bool unsubscribe) = 0;

    // feedback
    virtual QFuture<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId) = 0;
    virtual QFuture<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId) = 0;
    virtual QFuture<EventoResult<std::pair<int, std::vector<FeedbackNum>>>>
        getFeedbackSummaryListInPage(int page) = 0;
    virtual QFuture<EventoResult<int>> hasFeedbacked(EventoID event) = 0;
    virtual QFuture<EventoResult<bool>> feedbackEvent(const DTO_Feedback& feedback) = 0;
    virtual QFuture<EventoResult<DTO_Feedback>> getFeedbackInfo(EventoID event) = 0;

    // admin-fetch
    virtual QFuture<EventoResult<std::vector<DTO_UserBrief>>>
        getEventManagerList(EventoID eventoId) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_UserBrief>>> getAdminUserList() = 0;
    virtual QFuture<EventoResult<QString>> getAdminPermissionTreeData() = 0;
    virtual QFuture<EventoResult<QString>> getManagerPermissionTreeData() = 0;
    virtual QFuture<EventoResult<QVariantList>> getAdminEvents(const QString& userId) = 0;

    virtual ~Repository() = default;
};

Repository* getRepo();

#endif // REPOSITORY_H
