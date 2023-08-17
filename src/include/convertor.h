#ifndef CONVERTOR_H
#define CONVERTOR_H

#include "repository.h"
#include "evento.h"
#include "undertaking_evento.h"
#include "slide.h"
#include "latest_evento.h"
#include <feedback.h>
#include <permission_entry.h>
#include <user_brief.h>
#include <user.h>
#include <evento_brief.h>
#include <evento_block.h>

inline QString periodConvertor(const QDateTime& start, const QDateTime& end) {
    if (!start.isValid() || !end.isValid()) return {};
    if (start.date() == end.date())
        return start.toString("MM.dd hh:mm") + "-" + end.toString("hh:mm");
    else if (start.date().year() == end.date().year())
        return start.toString("MM.dd hh:mm") + " - " + end.toString("MM.dd hh:mm");
    return start.toString("yyyy.MM.dd hh:mm") + " - " + end.toString("yyyy.MM.dd hh:mm");
}

inline QString departmentConvertor(const std::vector<Department>& departments) {
    QString result;
    auto iter = departments.cbegin();
    if (iter != departments.cend()) {
        result += iter->name;
        ++iter;
    }
    while (iter != departments.cend()) {
        result += "，";
        result += iter->name;
        ++iter;
    }
    return result;
}

inline QString getFirstImageUrl(int eventId) {
    auto repository = getRepo();
    EventoException err;
    const auto& result = repository->get_event_slide_list(eventId, err);
    if (result.empty() || (int)err.code()) return "qrc:/res/image/banner_3.png";
    return result[0].url;
}

template<typename DTO, typename Entity>
struct Convertor {
    Entity operator()(const DTO& src) = delete;
};

template<typename DTO, typename Entity>
struct Convertor<std::vector<DTO>, std::vector<Entity>> {
    std::vector<Entity> operator()(const std::vector<DTO>& src) {
        std::vector<Entity> result;
        for (const auto& e : src) {
            result.emplace_back(Convertor<DTO, Entity>()(e));
        }
        return result;
    }
};

template<>
struct Convertor<DTO_Evento, Evento> {
    Evento operator()(const DTO_Evento& src) {
        return {
            src.id, src.title, src.state, src.description,
            periodConvertor(src.gmtEventStart, src.gmtEventEnd),
            periodConvertor(src.gmtRegistrationStart, src.gmtRegistrationEnd),
            departmentConvertor(src.departments),
            src.location, src.type, src.tag
        };
    }
};

template<>
struct Convertor<DTO_Evento, UndertakingEvento> {
    UndertakingEvento operator()(const DTO_Evento& e) {
        return {
                e.id, e.title,
                periodConvertor(e.gmtEventStart, e.gmtEventEnd),
                e.location, departmentConvertor(e.departments),
                getFirstImageUrl(e.id)
        };
    }
};

template<>
struct Convertor<DTO_Evento, LatestEvento> {
    LatestEvento operator()(const DTO_Evento& e) {
        return {
                e.id, e.title,
                periodConvertor(e.gmtEventStart, e.gmtEventEnd),
                departmentConvertor(e.departments),
                e.description, getFirstImageUrl(e.id)
        };
    }
};

template<>
struct Convertor<DTO_Evento, EventoBrief> {
    EventoBrief operator()(const DTO_Evento& e) {
		return {
				e.id, 
                e.title,
                e.state,
				e.description,
				periodConvertor(e.gmtEventStart, e.gmtEventEnd),
				getFirstImageUrl(e.id)
		};
	}
};

template<>
struct Convertor<DTO_Slide, Slide> {
    Slide operator()(const DTO_Slide& e) {
        return {
            e.id, e.title,
            e.link, e.url
        };
    }
};

template<>
struct Convertor<DTO_Feedback, Feedback> {
    Feedback operator()(const DTO_Feedback& src) {
        return {
            src.event,
            src.score,
            src.content,
            src.user
        };
    }
};

template<>
struct Convertor <DTO_Permission, PermissionEntry> {
PermissionEntry operator()(const DTO_Permission& src) {
		return {
            src.id,
            src.eventId,
            src.allMethodName
		};
	}
};

template<>
struct Convertor <DTO_UserBrief, UserBrief> {
    UserBrief operator()(const DTO_UserBrief& src) {
        // FIXME: 待后端确定接口
        return {};
    };
};

template<>
struct Convertor <DTO_User, User> {
    User operator()(const DTO_User& src) {
        // FIXME: 待后端确定接口
        return {};
    };
};

#endif
