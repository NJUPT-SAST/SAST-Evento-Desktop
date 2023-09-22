#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <dto/evento.h>
#include <dto/feedback.h>
#include <dto/feedback_summary.h>
#include <dto/permission.h>
#include <dto/slide.h>
#include <dto/user.h>
#include <dto/user_brief.h>

#include "evento_exception.h"
#include "result.h"
#include "types.h"

#include <QFuture>

struct Repository {
    // user-fetch
    virtual QStringList getAdminPermission(EventoException& err) = 0;
    virtual QStringList getManagerPermission(const EventoID &eventoId, EventoException& err) = 0;
    virtual QStringList getPermittedEvent(EventoException& err) = 0;
    virtual DTO_Permission getEventPermission(EventoID event, EventoException& err) = 0;
    virtual DTO_User getUserInfo(const UserID& id, EventoException& err) = 0;
    virtual ParticipationStatus getUserParticipate(const EventoID &eventoId, EventoException& err) = 0;
    virtual QFuture<EventoResult<DTO_Feedback>> getFeedbackInfo(const EventoID &eventoId, EventoException& err) = 0;

    // event-fetch
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList() = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListByTime(const QString& time) = 0;
    virtual QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId) = 0;
    virtual QFuture<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId) = 0;
    virtual QFuture<EventoResult<std::pair<int,std::vector<std::pair<int,int>>>>> getFeedbackSummaryListInPage(EventoID eventoId) = 0;
    virtual std::vector<DTO_Slide> getSlideList(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> getEventSlideList(EventoID id, EventoException& err) = 0;
    virtual QFuture<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(const int size) = 0;
    virtual QFuture<EventoResult<QString>> getTypeList() = 0;
    virtual QFuture<EventoResult<QString>> getLocationList() = 0;
    virtual QFuture<EventoResult<QString>> getDepartmentList() = 0;
    virtual QFuture<EventoResult<QString>> getSubscribedDepartmentList() = 0;
    virtual QFuture<EventoResult<QString>> getQRCode(const int& eventId) = 0;

    // event-upload
    virtual QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code) = 0;
    virtual QFuture<EventoResult<bool>> subscribe(EventoID event) = 0;
    virtual QFuture<EventoResult<bool>> hasFeedbacked(EventoID event) = 0;
    virtual bool feedbackEvent(const DTO_Feedback& code, EventoException& err) = 0;

    // admin-fetch
    virtual std::vector<DTO_Evento> getQualifiedEvent(EventoException& err, int type = -1, const std::vector<int> &dep = std::vector<int>(), const QDate &day = QDate()) = 0;
    virtual QStringList getActionStateList(EventoException& err) = 0;
    virtual QStringList getActionList(EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> getEventManagerList(const EventoID &eventoId, EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> getAdminUserList(EventoException& err) = 0;
    virtual QString getAdminPermissionTreeData(EventoException& err) = 0;
    virtual QString getManagerPermissionTreeData(EventoException& err) = 0;

    virtual ~Repository() = default;
};

Repository* getRepo();

#endif  // REPOSITORY_H
