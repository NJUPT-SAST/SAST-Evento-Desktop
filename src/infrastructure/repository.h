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
    virtual DTO_PermissionTree get_admin_permission(EventoException& err) = 0;
    virtual DTO_PermissionTree get_manager_permission(const EventoID &eventoId, EventoException& err) = 0;
    virtual QStringList get_permitted_event(EventoException& err) = 0;
    virtual DTO_Permission get_event_permission(EventoID event, EventoException& err) = 0;
    virtual DTO_User get_user_info(const UserID& id, EventoException& err) = 0;
    virtual ParticipationStatus get_user_participate(const EventoID &eventoId, EventoException& err) = 0;
    virtual DTO_Feedback get_feedback_info(const EventoID &eventoId, EventoException& err) = 0;

    // event-fetch
    virtual std::vector<DTO_Evento> get_undertaking_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_latest_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_subscribed_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_history_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_event_list(const int& page, const int& size, EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_department_event_list(const int& departmentId, EventoException &err) = 0;
    virtual DTO_Evento get_event(EventoID event, EventoException& err) = 0;
    virtual std::vector<DTO_Feedback> get_feedback_list(EventoID eventoId, EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_slide_list(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_event_slide_list(EventoID id, EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_home_slide_list(const int& size, EventoException& err) = 0;
    virtual QString get_type_list(EventoException& err) = 0;
    virtual QString get_location_list(EventoException& err) = 0;
    virtual QString get_department_list(EventoException& err) = 0;
    virtual QString get_qrcode(const int& eventId, EventoException& err) = 0;

    // event-upload
    virtual bool event_checkin(EventoID event, const QString& code, EventoException& err) = 0;
    virtual bool event_feedback(const DTO_Feedback& code, EventoException& err) = 0;
    virtual bool event_subscribe(EventoID event, EventoException& err) = 0;
    virtual bool is_feedback(EventoID event, EventoException& err) = 0;

    // admin-fetch
    virtual std::vector<DTO_Evento> get_qualified_event(EventoException& err, int type = -1, const std::vector<int> &dep = std::vector<int>(), const QDate &day = QDate()) = 0;
    virtual QStringList get_action_state_list(EventoException& err) = 0;
    virtual QStringList get_action_list(EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> get_event_manager_list(const EventoID &eventoId, EventoException& err) = 0;
    virtual std::vector<DTO_UserBrief> get_admin_user_list(EventoException& err) = 0;
    virtual QString get_admin_permission_treeData(EventoException& err) = 0;
    virtual QString get_manager_permission_treeData(EventoException& err) = 0;
};

Repository* getRepo();

#endif  // REPOSITORY_H
