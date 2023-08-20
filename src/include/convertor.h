#ifndef CONVERTOR_H
#define CONVERTOR_H

#include "repository.h"
#include "evento.h"
#include "undertaking_evento.h"
#include "slide.h"
#include "latest_evento.h"

inline QString periodConvertor(const QDateTime& start, const QDateTime& end) {
    if (!start.isValid() || !end.isValid()) return {};
    if (start.date() == end.date())
        return start.toString("MM.dd hh:mm") + "-" + end.toString("hh:mm");
    else if (start.date().year() == end.date().year())
        return start.toString("MM.dd hh:mm") + " - " + end.toString("MM.dd hh:mm");
    return start.toString("yyyy.MM.dd hh:mm") + " - " + end.toString("yyyy.MM.dd hh:mm");
}

inline QString departmentConvertor(const std::vector<Department>& departments) {
    if (departments.empty()) return {};
    if (departments.size() == 1) {
        return departments.begin()->name;
    }
    QString result;
    for (const auto& department : departments) {
        result += ("，" + department.name);
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
    Entity operator()(const DTO& src);
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
struct Convertor<std::vector<DTO_Evento>, std::vector<UndertakingEvento>> {
    std::vector<UndertakingEvento> operator()(const std::vector<DTO_Evento>& src) {
        std::vector<UndertakingEvento> result;
        for (const auto& e : src) {
            result.emplace_back(UndertakingEvento{
                e.id, e.title,
                periodConvertor(e.gmtEventStart, e.gmtEventEnd),
                e.location, departmentConvertor(e.departments),
                getFirstImageUrl(e.id)
            });
        }
        return result;
    }
};

template<>
struct Convertor<std::vector<DTO_Evento>, std::vector<LatestEvento>> {
    std::vector<LatestEvento> operator()(const std::vector<DTO_Evento>& src) {
        std::vector<LatestEvento> result;
        for (const auto& e : src) {
            result.emplace_back(LatestEvento{
                e.id, e.title,
                periodConvertor(e.gmtEventStart, e.gmtEventEnd),
                departmentConvertor(e.departments),
                e.description, getFirstImageUrl(e.id)
            });
        }
        return result;
    }
};

template<>
struct Convertor<std::vector<DTO_Slide>, std::vector<Slide>> {
    std::vector<Slide> operator()(const std::vector<DTO_Slide>& src) {
        if (src.empty())
            return std::vector<Slide>{
                Slide{0, "SAST Evento", "", "qrc:/res/image/banner_3.png"}
            };
        std::vector<Slide> result;
        for (const auto& e : src) {
            result.emplace_back(Slide{
                e.id, e.title,
                e.link, e.url
            });
        }
        return result;
    }
};

#endif
