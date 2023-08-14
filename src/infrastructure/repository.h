#ifndef DTO_USER_H
#define DTO_USER_H

#include "types.h"
#include "evento_exception.h"
#include <dto/evento.h>
#include <dto/feedback.h>
#include <dto/permission.h>
#include <dto/slide.h>

class Repository {
    //user-fetch
    virtual QStringList get_admin_permission(EventoException& err) = 0;
    virtual QStringList get_permitted_event(EventoException& err) = 0;
    virtual DTO_Permission get_event_permission(EventoID event, EventoException& err) = 0;

    //event-fetch
    virtual std::vector<DTO_Evento> get_undertaking_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_latest_list(EventoException& err) = 0;
    virtual std::vector<DTO_Evento> get_subscribed_list(EventoException& err) = 0;
    virtual DTO_Evento get_event(EventoID event, EventoException& err) = 0;
    virtual std::vector<DTO_Feedback> get_feedback_list(EventoException& err) = 0;
    virtual std::vector<DTO_Slide> get_slide_list(EventoException& err) = 0;

    //event-upload
    virtual bool event_checkin(EventoID event, const QString& code, EventoException& err) = 0;
    virtual bool event_feedback(const DTO_Feedback& code, EventoException& err) = 0;
    virtual bool event_subscribe(EventoID event, EventoException& err) = 0;

    //admin-fetch
    virtual std::vector<DTO_Evento> get_qualified_event(int type, std::vector<int> dep, QDate day, EventoException& err) = 0;
};

#endif // DTO_USER_H
