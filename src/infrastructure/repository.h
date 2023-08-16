#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "types.h"
#include "evento_exception.h"
#include <dto/evento.h>
#include <dto/feedback.h>
#include <dto/permission.h>
#include <dto/slide.h>
#include <dto/user.h>
#include <dto/user_brief.h>

class Repository {
    //user-fetch
    virtual QStringList get_admin_permission(EventoException& err) = 0;
    virtual QStringList get_permitted_event(EventoException& err) = 0;
    virtual DTO_Permission get_event_permission(EventoID event, EventoException& err) = 0;
    virtual DTO_User get_user_info(const UserID &id, EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_home_slide_list(const int &size, EventoException& err) = 0;

    //event-fetch
    virtual std::vector<DTO_Evento> get_undertaking_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_latest_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_subscribed_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_history_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_event_list(const int &page, const int &size, EventoException& err) = 0;
    virtual DTO_Evento get_event(EventoID event, EventoException& err) = 0;
    virtual std::vector<DTO_Feedback> get_feedback_list(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_slide_list(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_event_slide_list(EventoID id, EventoException& err) = 0;
    virtual std::vector<EventType> get_type_list(const int &page, const int &size, EventoException& err) = 0;
    virtual std::vector<Location> get_location_list(EventoException& err) = 0;
    virtual QString get_qrcode(const int &eventId, EventoException& err) = 0;

    //event-upload
    virtual bool event_checkin(EventoID event, const QString& code, EventoException& err) = 0;
    virtual bool event_feedback(const DTO_Feedback& code, EventoException& err) = 0;
    virtual bool event_subscribe(EventoID event, EventoException& err) = 0;

    //admin-fetch
    virtual std::vector<DTO_Evento> get_qualified_event(int type, const std::vector<int> &dep, const QDate &day, EventoException& err) = 0;
    virtual QStringList get_action_state_list(EventoException& err) = 0;
    virtual QStringList get_action_list(EventoException& err) = 0;
};

#endif // DTO_USER_H
