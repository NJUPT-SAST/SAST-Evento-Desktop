#include "evento_service.h"
#include "calendar.h"
#include "convertor.h"
#include "department_events.h"
#include "evento.h"
#include "evento_block_model.h"
#include "evento_brief_model.h"
#include "evento_edit.h"
#include "evento_helper.h"
#include "evento_info.h"
#include "feedback_service.h"
#include "image.h"
#include "latest_evento_model.h"
#include "my_page.h"
#include "plaza.h"
#include "repository.h"
#include "schedule.h"
#include "scheduled_evento.h"
#include "scheduled_evento_model.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"
#include "user_helper.h"

#include <QDateTime>

#include <algorithm>
#include <array>
#include <set>
#include <vector>

void EventoService::load_Plaza() {
    std::array<QFuture<bool>, 2> tasks = {
        getRepo()->getUndertakingList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result) {
                PlazaController::getInstance()->onPlazaLoadFailure(result);
                return false;
            }
            auto data = result.take();
            std::vector<UndertakingEvento> model;
            {
                std::lock_guard lock(mutex);
                undertaking.clear();
                for (auto& i : data) {
                    undertaking.push_back(i.id);
                    model.push_back(UndertakingEvento(i));
                    stored[i.id] = std::move(i);
                }
            }
            UndertakingEventoModel::getInstance()->resetModel(std::move(model));
            return true;
        }),
        getRepo()->getLatestList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result) {
                PlazaController::getInstance()->onPlazaLoadFailure(result);
                return false;
            }
            auto data = result.take();
            std::vector<LatestEvento> model;
            {
                std::lock_guard lock(mutex);
                latest.clear();
                for (auto& i : data) {
                    latest.push_back(i.id);
                    model.push_back(LatestEvento(i));
                    stored[i.id] = std::move(i);
                }
            }
            LatestEventoModel::getInstance()->resetModel(std::move(model));
            return true;
        })};
    QtFuture::whenAll(tasks.begin(), tasks.end()).then([](QList<QFuture<bool>> jobs) {
        for (auto& i : jobs)
            if (i.isCanceled() || !i.takeResult())
                return;
        PlazaController::getInstance()->onPlazaLoadFinished();
    });
}

void EventoService::load_RegisteredSchedule() {
    getRepo()->getRegisteredList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            ScheduleController::getInstance()->onLoadRegisteredFailure(result.message());
            return;
        }
        auto data = result.take();
        std::vector<Schedule> multiDayEvents;
        std::vector<Schedule> singleDayEvents;
        {
            std::lock_guard lock(mutex);
            registered.clear();
            for (auto& evento : data) {
                registered.push_back(evento.id);
                auto participation = getRepo()->getUserParticipate(evento.id).takeResult();
                auto has_feedback = getRepo()->hasFeedbacked(evento.id).takeResult();
                if (participation &&
                    (has_feedback || has_feedback.code() == EventoExceptionCode::FalseValue)) {
                    if (evento.gmtEventStart == evento.gmtEventEnd)
                        singleDayEvents.emplace_back(evento, participation.take(), has_feedback);
                    else
                        multiDayEvents.emplace_back(evento, participation.take(), has_feedback);
                } else {
                    ScheduleController::getInstance()->onLoadRegisteredFailure(result.message());
                    return;
                }
                stored[evento.id] = std::move(evento);
            }
        }
        std::sort(singleDayEvents.begin(), singleDayEvents.end(),
                  [](const Schedule& e1, const Schedule& e2) {
                      auto date1 = QDate::fromString(e1.date, "MM.dd");
                      auto date2 = QDate::fromString(e2.date, "MM.dd");
                      return date1 > date2;
                  });
        std::vector<Schedule> model(multiDayEvents.begin(), multiDayEvents.end());
        model.insert(model.end(), singleDayEvents.begin(), singleDayEvents.end());
        std::set<QString> dateSet;
        int width = 110;
        std::for_each(model.begin(), model.end(), [&dateSet, &width](Schedule& e) {
            auto size = dateSet.size();
            dateSet.insert(e.date);
            if (dateSet.size() == size) {
                e.hasSameDate = true;
                width += 20;
            }
            width += 90;
        });
        ScheduleController::getInstance()->setProperty("width", width);
        ScheduledEventoModel::getInstance()->resetModel(std::move(model));
        ScheduleController::getInstance()->onLoadSubscribedFinished();
    });
}

void EventoService::load_SubscribedSchedule() {
    getRepo()->getSubscribedList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            ScheduleController::getInstance()->onLoadSubscribedFailure(result.message());
            return;
        }
        auto data = result.take();
        std::vector<Schedule> multiDayEvents;
        std::vector<Schedule> singleDayEvents;
        {
            std::lock_guard lock(mutex);
            subscribed.clear();
            for (auto& evento : data) {
                registered.push_back(evento.id);
                auto participation = getRepo()->getUserParticipate(evento.id).takeResult();
                auto has_feedback = getRepo()->hasFeedbacked(evento.id).takeResult();
                if (participation &&
                    (has_feedback || has_feedback.code() == EventoExceptionCode::FalseValue)) {
                    if (evento.gmtEventStart == evento.gmtEventEnd)
                        singleDayEvents.emplace_back(evento, participation.take(), has_feedback);
                    else
                        multiDayEvents.emplace_back(evento, participation.take(), has_feedback);
                } else {
                    ScheduleController::getInstance()->onLoadSubscribedFailure(result.message());
                    return;
                }
                stored[evento.id] = std::move(evento);
            }
        }
        std::sort(singleDayEvents.begin(), singleDayEvents.end(),
                  [](const Schedule& e1, const Schedule& e2) {
                      auto date1 = QDate::fromString(e1.date, "MM.dd");
                      auto date2 = QDate::fromString(e2.date, "MM.dd");
                      return date1 > date2;
                  });
        std::vector<Schedule> model(multiDayEvents.begin(), multiDayEvents.end());
        model.insert(model.end(), singleDayEvents.begin(), singleDayEvents.end());
        std::set<QString> dateSet;
        int width = 110;
        std::for_each(model.begin(), model.end(), [&dateSet, &width](Schedule& e) {
            auto size = dateSet.size();
            dateSet.insert(e.date);
            if (dateSet.size() == size) {
                e.hasSameDate = true;
                width += 90;
            } else
                width += 110;
        });
        ScheduleController::getInstance()->setProperty("width", width);
        ScheduledEventoModel::getInstance()->resetModel(std::move(model));
        ScheduleController::getInstance()->onLoadSubscribedFinished();
    });
}

void EventoService::load_DepartmentEvents(int departmentId) {
    getRepo()
        ->getDepartmentEventList(departmentId)
        .then([this](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result) {
                DepartmentEventsController::getInstance()->onLoadDepartmentEventFailure(
                    result.message());
                return;
            }
            auto data = result.take();
            std::vector<EventoBrief> model;
            {
                std::lock_guard lock(mutex);
                departmentEvento.clear();
                for (auto& i : data) {
                    departmentEvento.push_back(i.id);
                    model.push_back(EventoBrief(i));
                    stored[i.id] = std::move(i);
                }
            }
            EventoBriefModel::getInstance()->resetModel(std::move(model));
            DepartmentEventsController::getInstance()->onLoadDepartmentEventFinished();
        });
}

void EventoService::load_History() {
    getRepo()->getHistoryList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            MyPageController::getInstance()->onLoadFailure(result.message());
            return;
        }
        auto data = result.take();
        std::vector<EventoBrief> model;
        {
            std::lock_guard lock(mutex);
            history.clear();
            for (auto& i : data) {
                history.push_back(i.id);
                model.push_back(EventoBrief(i));
                stored[i.id] = std::move(i);
            }
        }
        EventoBriefModel::getInstance()->resetModel(std::move(model));
        MyPageController::getInstance()->onLoadFinished();
    });
}

void EventoService::load_Block(QDate date) {
    CalendarController::getInstance();
    date = getMonday(date);
    getRepo()->getEventListAfterTime(date).then([=](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            CalendarController::getInstance()->onLoadAllFailure(result.message());
            return;
        }
        auto permitted_list =
            getRepo()
                ->getPermittedEvents(UserHelper::getInstance()->property("userId").toString())
                .takeResult();
        if (!permitted_list) {
            CalendarController::getInstance()->onLoadAllFailure(result.message());
            return;
        }
        auto permitted = permitted_list.take();
        auto data = result.take();
        std::vector<EventoBlock> model;
        auto sunday = date.addDays(6);
        {
            std::lock_guard lock(mutex);
            blocks.clear();
            for (auto& i : data) {
                if (i.gmtEventStart.date() > sunday)
                    continue;
                blocks.push_back(i.id);
                model.emplace_back(i, permitted);
                stored[i.id] = std::move(i);
            }
        }
        EventoBlockModel::getInstance()->resetModel(date, std::move(model));
        CalendarController::getInstance()->onLoadAllFinished();
    });
}

void EventoService::load_Event(EventoID id) {
    getRepo()->getEventById(id).then([=](EventoResult<DTO_Evento> result) {
        if (!result) {
            EventoInfoController::getInstance()->onLoadFailure(result.message());
            return;
        }
        {
            std::lock_guard lock(mutex);
            const auto& event = (stored[id] = std::move(result.take()));
            EventoHelper::getInstance()->update(event);
            SlideModel::getInstance()->resetModel(
                ImageManagement::pictureConvertor(event.departments));
        }
        EventoInfoController::getInstance()->onLoadFinished();
    });
}

void EventoService::load(EventoID id) {
    std::array<QFuture<bool>, 2> tasks = {
        getRepo()->getEventById(id).then([=](EventoResult<DTO_Evento> result) {
            if (!result) {
                EventoInfoController::getInstance()->onLoadFailure(result.message());
                return false;
            }
            Evento event;
            {
                std::lock_guard lock(mutex);
                event = (stored[id] = std::move(result.take()));
            }
            EventoHelper::getInstance()->update(event);
            SlideModel::getInstance()->resetModel(
                ImageManagement::pictureConvertor(stored[id].departments));
            return true;
        }),
        getRepo()->getUserParticipate(id).then([this](EventoResult<ParticipationStatus> result) {
            if (UserHelper::getInstance()->property("permission").toInt() == 1)
                return true;
            if (!result) {
                EventoInfoController::getInstance()->onLoadFailure(result.message());
                return false;
            }
            auto participate = result.take();
            {
                std::lock_guard lock(mutex);
                EventoInfoController::getInstance()->setProperty("isRegistrated",
                                                                 participate.isRegistrated);
                EventoInfoController::getInstance()->setProperty("isParticipated",
                                                                 participate.isParticipated);
                EventoInfoController::getInstance()->setProperty("isSubscribed",
                                                                 participate.isSubscribed);
            }
            return true;
        })};
    QtFuture::whenAll(tasks.begin(), tasks.end()).then([](QList<QFuture<bool>> tasks) {
        for (auto& i : tasks)
            if (i.isCanceled() || !i.takeResult())
                return;
        EventoInfoController::getInstance()->onLoadFinished();
    });
    if (UserHelper::getInstance()->property("permission").toInt() != 1)
        FeedbackService::getInstance().load_UserFeedback(id);
}

DTO_Evento EventoService::edit(EventoID id) {
    std::shared_lock guard(mutex);
    return stored[id];
}

void EventoService::create(const QString& title, const QString& description,
                           const QString& eventStart, const QString& eventEnd,
                           const QString& registerStart, const QString& registerEnd, int typeId,
                           int locationId, const QVariantList& departmentIds, const QString& tag) {
    getRepo()
        ->createEvent(title, description, timeConvertor(eventStart), timeConvertor(eventEnd),
                      timeConvertor(registerStart), timeConvertor(registerEnd), typeId, locationId,
                      departmentIds, tag)
        .then([](EventoResult<bool> result) {
            if (!result) {
                EventoEditController::getInstance()->onCreateFailure(result.message());
                return;
            }
            EventoEditController::getInstance()->onCreateFinished();
        });
}

void EventoService::edit(EventoID id, const QString& title, const QString& description,
                         const QString& eventStart, const QString& eventEnd,
                         const QString& registerStart, const QString& registerEnd, int typeId,
                         int locationId, const QVariantList& departmentIds, const QString& tag) {
    getRepo()
        ->editEvent(id, title, description, timeConvertor(eventStart), timeConvertor(eventEnd),
                    timeConvertor(registerStart), timeConvertor(registerEnd), typeId, locationId,
                    departmentIds, tag)
        .then([](EventoResult<bool> result) {
            if (!result) {
                EventoEditController::getInstance()->onCreateFailure(result.message());
                return;
            }
            EventoEditController::getInstance()->onCreateFinished();
        });
}

void EventoService::getQRCode(EventoID id) {
    getRepo()->getQRCode(id).then([](EventoResult<QString> result) {
        if (!result) {
            CalendarController::getInstance()->onLoadCheckCodeFailure(result.message());
            return;
        }
        auto code = result.take();
        CalendarController::getInstance()->onLoadCheckCodeFinished(code);
    });
}

void EventoService::del(EventoID id) {
    getRepo()->deleteEvent(id).then([](EventoResult<bool> result) {
        if (!result) {
            CalendarController::getInstance()->onDeleteFailure(result.message());
            return;
        }
        CalendarController::getInstance()->onDeleteFinished();
    });
}

void EventoService::cancel(EventoID id) {
    getRepo()->cancelEvent(id).then([](EventoResult<bool> result) {
        if (!result) {
            CalendarController::getInstance()->onCancelFailure(result.message());
            return;
        }
        CalendarController::getInstance()->onCancelFinished();
    });
}

void EventoService::subscribeDepartment(int departmentId, bool unsubscribe) {
    getRepo()->subscribeDepartment(departmentId, unsubscribe).then([](EventoResult<bool> result) {
        if (!result) {
            DepartmentEventsController::getInstance()->onSubscribeFailure(result.message());
            return;
        }
        DepartmentEventsController::getInstance()->onSubscribeFinished();
    });
}

Evento::Evento(const DTO_Evento& src)
    : id(src.id), title(src.title), description(src.description), type(src.type),
      location(src.location), tag(src.tag), state(src.state) {

    this->department = departmentConvertor(src.departments);
    this->eventTime = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->registrationTime = periodConvertor(src.gmtRegistrationStart, src.gmtRegistrationEnd);
}

Schedule::Schedule(const DTO_Evento& src, const ParticipationStatus& participate, bool hasFeedback)
    : id(src.id), title(src.title), state(src.state), location(src.location),
      isChecked(participate.isParticipated), hasFeedback(hasFeedback) {

    this->department = departmentConvertor(src.departments);

    if (src.gmtEventStart.date() == src.gmtEventEnd.date()) {
        this->date = src.gmtEventStart.toString(QStringLiteral("MM.dd"));
        this->startTime = src.gmtEventStart.toString(QStringLiteral("hh:mm"));
        this->endTime = src.gmtEventEnd.toString(QStringLiteral("hh:mm"));
    } else {
        this->date = "Multi-day";
        this->startTime = "Many";
        this->endTime = "Days";
    }
}

UndertakingEvento::UndertakingEvento(const DTO_Evento& src)
    : id(src.id), title(src.title), location(src.location) {

    this->time = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->department = departmentConvertor(src.departments);
    this->image = ImageManagement::pictureConvertor(src.departments).at(0);
}

LatestEvento::LatestEvento(const DTO_Evento& src)
    : id(src.id), title(src.title), description(src.description) {

    this->time = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->department = departmentConvertor(src.departments);
    this->image = ImageManagement::pictureConvertor(src.departments).at(0);
}

EventoBrief::EventoBrief(const DTO_Evento& src)
    : id(src.id), title(src.title), description(src.description), location(src.location) {

    this->time = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->department = departmentConvertor(src.departments);
    this->image = ImageManagement::pictureConvertor(src.departments).at(0);
}

EventoBlock::EventoBlock(const DTO_Evento& src, const std::set<EventoID>& permitted)
    : id(src.id), title(src.title), gmtEventStart(src.gmtEventStart), gmtEventEnd(src.gmtEventEnd),
      editable(permitted.count(src.id)) {
    init();
}
