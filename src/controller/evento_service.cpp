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
#include "scheduled_evento_model.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"
#include "user_helper.h"

#include <array>

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
                    undertaking.push_back(i.id);
                    model.push_back(LatestEvento(i));
                    stored[i.id] = std::move(i);
                }
            }
            LatestEventoModel::getInstance()->resetModel(std::move(model));
            return true;
        })};
    QtFuture::whenAll(tasks.begin(), tasks.end()).then([](QList<QFuture<bool>> jobs) {
        for (auto& i : jobs)
            if (!i.takeResult())
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
        std::vector<Schedule> model;
        {
            std::lock_guard lock(mutex);
            registered.clear();
            for (auto& evento : data) {
                registered.push_back(evento.id);
                auto participation = getRepo()->getUserParticipate(evento.id).takeResult();
                auto has_feedback = getRepo()->hasFeedbacked(evento.id).takeResult();
                if (participation &&
                    (has_feedback || has_feedback.code() == EventoExceptionCode::FalseValue))
                    model.push_back(Schedule(evento, participation.take(), has_feedback));
                else {
                    ScheduleController::getInstance()->onLoadRegisteredFailure(result.message());
                    return;
                }
                stored[evento.id] = std::move(evento);
            }
        }
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
        std::vector<Schedule> model;
        {
            std::lock_guard lock(mutex);
            subscribed.clear();
            for (auto& evento : data) {
                subscribed.push_back(evento.id);
                auto participation = getRepo()->getUserParticipate(evento.id).takeResult();
                auto has_feedback = getRepo()->hasFeedbacked(evento.id).takeResult();
                if (participation &&
                    (has_feedback || has_feedback.code() == EventoExceptionCode::FalseValue))
                    model.push_back(Schedule(evento, participation.take(), has_feedback));
                else {
                    ScheduleController::getInstance()->onLoadSubscribedFailure(result.message());
                    return;
                }
                stored[evento.id] = std::move(evento);
            }
        }
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

void EventoService::load_Block(const QString& date) {
    this->date = QDate::fromString(date, "yyyy-M-d");

    getRepo()->getEventListByTime(date).then([this](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            CalendarController::getInstance()->onLoadAllFailure(result.message());
            return;
        }
        auto id_filter =
            getRepo()
                ->getPermittedEvents(UserHelper::getInstance()->property("userId").toString())
                .takeResult();
        if (!id_filter) {
            CalendarController::getInstance()->onLoadAllFailure(result.message());
            return;
        }
        auto filter_data = id_filter.take();
        auto data = result.take();
        std::vector<EventoBlock> model;
        {
            std::lock_guard lock(mutex);
            blocks.clear();
            for (auto& i : data) {
                blocks.push_back(i.id);
                model.emplace_back(i, filter_data);
                stored[i.id] = std::move(i);
            }
        }
        EventoBlockModel::getInstance()->resetModel(std::move(model));
        CalendarController::getInstance()->onLoadAllFinished();
    });
}

void EventoService::load_Event(EventoID id) {
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
            if (!i.takeResult())
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
      location(src.location), tag(src.tag), state(stateConvertor(src.state)) {

    this->department = departmentConvertor(src.departments);
    this->eventTime = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->registrationTime = periodConvertor(src.gmtRegistrationStart, src.gmtRegistrationEnd);
}

Schedule::Schedule(const DTO_Evento& src, const ParticipationStatus& participate, bool hasFeedback)
    : id(src.id), title(src.title), state(stateConvertor(src.state)), location(src.location),
      isChecked(participate.isParticipated), hasFeedback(hasFeedback) {

    this->department = departmentConvertor(src.departments);

    auto start = QDateTime::fromString(src.gmtEventStart, "yyyy-MM-dd hh:mm:ss");
    auto end = QDateTime::fromString(src.gmtEventEnd, "yyyy-MM-dd hh:mm:ss");
    if (start.date() == end.date()) {
        this->date = start.toString(QStringLiteral("MM月dd日"));
        this->startTime = start.toString(QStringLiteral("hh:mm"));
        this->endTime = end.toString(QStringLiteral("hh:mm"));
    } else {
        this->date = "多天事件";
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

bool areDatesInSameWeek(const QDate& date1, const QDate& date2) {
    int week1 = date1.dayOfWeek();
    int week2 = date2.dayOfWeek();

    QDate firstDayOfWeek1 = date1.addDays(-week1 + 1);
    QDate lastDayOfWeek1 = date1.addDays(7 - week1);
    QDate firstDayOfWeek2 = date2.addDays(-week2 + 1);
    QDate lastDayOfWeek2 = date2.addDays(7 - week2);

    return (date1 >= firstDayOfWeek2 && date1 <= lastDayOfWeek2) ||
           (date2 >= firstDayOfWeek1 && date2 <= lastDayOfWeek1);
}

EventoBlock::EventoBlock(const DTO_Evento& src, const std::set<EventoID>& eventList)
    : id(src.id), title(src.title), time(periodConvertor(src.gmtEventStart, src.gmtEventEnd)),
      editable(eventList.count(src.id)) {

    auto gmtEventStart = QDateTime::fromString(src.gmtEventStart, "yyyy-MM-dd hh:mm:ss");
    auto gmtEventEnd = QDateTime::fromString(src.gmtEventEnd, "yyyy-MM-dd hh:mm:ss");

    if (gmtEventStart.date() == gmtEventEnd.date()) {
        rowStart = gmtEventStart.time().hour() - 7;
        if (rowStart < 1)
            rowStart = 1;
        else
            rowStart += gmtEventStart.time().minute() / 60.0;

        rowEnd = gmtEventEnd.time().hour() - 7;
        if (rowEnd > 16)
            rowEnd = 16;

        columnEnd = columnStart = gmtEventStart.date().dayOfWeek() - 1;
    } else {
        rowStart = 0;
        rowEnd = 1;

        auto now = EventoService::getInstance().getDate();

        if (areDatesInSameWeek(gmtEventStart.date(), now))
            columnStart = gmtEventStart.date().dayOfWeek() - 1;
        else
            columnStart = 0;

        if (areDatesInSameWeek(gmtEventEnd.date(), now))
            columnEnd = gmtEventEnd.date().dayOfWeek() - 1;
        else
            columnEnd = 6;
    }
}
