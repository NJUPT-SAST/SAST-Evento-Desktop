#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <dto/evento.h>
#include <dto/feedback.h>
#include <dto/permission.h>
#include <dto/slide.h>
#include <dto/user.h>
#include <dto/user_brief.h>

#include "evento_exception.h"
#include "types.h"

struct Repository {
    // user-fetch
    virtual QStringList getAdminPermission(EventoException& err) = 0;
    virtual QStringList getManagerPermission(const EventoID &eventoId, EventoException& err) = 0;
    virtual QStringList getPermittedEvent(EventoException& err) = 0;
    virtual DTO_Permission getEventPermission(EventoID event, EventoException& err) = 0;
    virtual DTO_User getUserInfo(const UserID& id, EventoException& err) = 0;
    virtual ParticipationStatus getUserParticipate(const EventoID &eventoId, EventoException& err) = 0;
    virtual DTO_Feedback getFeedbackInfo(const EventoID &eventoId, EventoException& err) = 0;

    // event-fetch
    virtual std::vector<DTO_Evento> getUndertakingList(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> getLatestList(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> getRegisteredList(EventoException &err) = 0;
    virtual std::vector<DTO_Evento> getSubscribedList(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> getHistoryList(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> getEventList(const int& page, const int& size, EventoException& err) = 0;
    virtual std::vector<DTO_Evento> getDepartmentEventList(const int& departmentId, EventoException &err) = 0;
    virtual DTO_Evento getEvent(EventoID event, EventoException& err) = 0;
    virtual std::vector<DTO_Feedback> getFeedbackList(EventoID eventoId, EventoException& err) = 0;
    virtual std::vector<DTO_Slide> getSlideList(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> getEventSlideList(EventoID id, EventoException& err) = 0;
    virtual std::vector<DTO_Slide> getHomeSlideList(const int& size, EventoException& err) = 0;
    virtual QString getTypeList(EventoException& err) = 0;
    virtual QString getLocationList(EventoException& err) = 0;
    virtual QString getDepartmentList(EventoException& err) = 0;
    virtual QString getQRCode(const int& eventId, EventoException& err) = 0;

    // event-upload
    virtual bool checkInEvent(EventoID event, const QString& code, EventoException& err) = 0;
    virtual bool feedbackEvent(const DTO_Feedback& code, EventoException& err) = 0;
    virtual bool subscribeEvent(EventoID event, EventoException& err) = 0;
    virtual bool isFeedbacked(EventoID event, EventoException& err) = 0;

    // admin-fetch
    virtual std::vector<DTO_Evento> getQualifiedEvent(EventoException& err, int type = -1, const std::vector<int> &dep = std::vector<int>(), const QDate &day = QDate()) = 0;
    virtual QStringList getActionStateList(EventoException& err) = 0;
    virtual QStringList getActionList(EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> getEventManagerList(const EventoID &eventoId, EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> getAdminUserList(EventoException& err) = 0;
    virtual QString getAdminPermissionTreeData(EventoException& err) = 0;
    virtual QString getManagerPermissionTreeData(EventoException& err) = 0;
};

Repository* getRepo();

#endif  // REPOSITORY_H
