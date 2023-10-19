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

#include <QtConcurrent>
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

    QtConcurrent::run([=]() {
        for (const auto& i : tasks)
            if (!i.result())
                return;
        PlazaController::getInstance()->onPlazaLoadFinished();
    });
}

void EventoService::load_RegisteredSchedule() {
    auto future =
        getRepo()->getRegisteredList().then([=](EventoResult<std::vector<DTO_Evento>> result) {
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
                    auto participateFuture = getRepo()->getUserParticipate(evento.id).then(
                        [=](EventoResult<ParticipationStatus> result) {
                            if (!result) {
                                ScheduleController::getInstance()->onLoadRegisteredFailure(
                                    result.message());
                                return ParticipationStatus{};
                            }
                            auto participate = result.take();
                            return participate;
                        });
                    auto hasFeedbackedFuture =
                        getRepo()->hasFeedbacked(evento.id).then([=](EventoResult<int> result) {
                            if (!result) {
                                ScheduleController::getInstance()->onLoadRegisteredFailure(
                                    result.message());
                                return false;
                            }
                            bool hasFeedbackedFuture = result.take();
                            return hasFeedbackedFuture;
                        });
                    model.push_back(
                        Schedule(evento, participateFuture.result(), hasFeedbackedFuture.result()));
                    stored[evento.id] = std::move(evento);
                }
            }
            ScheduledEventoModel::getInstance()->resetModel(std::move(model));
            ScheduleController::getInstance()->onLoadSubscribedFinished();
        });

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::load_SubscribedSchedule() {
    auto future =
        getRepo()->getSubscribedList().then([=](EventoResult<std::vector<DTO_Evento>> result) {
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
                    registered.push_back(evento.id);
                    auto participateFuture = getRepo()->getUserParticipate(evento.id).then(
                        [=](EventoResult<ParticipationStatus> result) {
                            if (!result) {
                                ScheduleController::getInstance()->onLoadRegisteredFailure(
                                    result.message());
                                return ParticipationStatus{};
                            }
                            auto participate = result.take();
                            return participate;
                        });
                    auto hasFeedbackedFuture =
                        getRepo()->hasFeedbacked(evento.id).then([=](EventoResult<int> result) {
                            if (!result) {
                                ScheduleController::getInstance()->onLoadRegisteredFailure(
                                    result.message());
                                return false;
                            }
                            bool hasFeedbackedFuture = result.take();
                            return hasFeedbackedFuture;
                        });
                    model.push_back(
                        Schedule(evento, participateFuture.result(), hasFeedbackedFuture.result()));
                    stored[evento.id] = std::move(evento);
                }
            }
            ScheduledEventoModel::getInstance()->resetModel(std::move(model));
            ScheduleController::getInstance()->onLoadSubscribedFinished();
        });

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::load_DepartmentEvents(int departmentId) {
    auto future =
        getRepo()
            ->getDepartmentEventList(departmentId)
            .then([=](EventoResult<std::vector<DTO_Evento>> result) {
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

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::load_History() {
    auto future =
        getRepo()->getHistoryList().then([=](EventoResult<std::vector<DTO_Evento>> result) {
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

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::load_Block(const QString& date) {
    this->date = QDate::fromString(date, "yyyy-M-d");
    auto future1 =
        getRepo()
            ->getAdminEvents(UserHelper::getInstance()->property("userId").toString())
            .then([=](EventoResult<QVariantList> result) {
                if (!result) {
                    CalendarController::getInstance()->onLoadAllFailure(result.message());
                    return QVariantList{-1};
                }
                return result.take();
            });
    auto future2 =
        getRepo()->getEventListByTime(date).then([=](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result) {
                CalendarController::getInstance()->onLoadAllFailure(result.message());
                return;
            }
            auto f(future1);
            auto eventList = f.result();
            if (eventList.contains(-1))
                return;
            auto data = result.take();

            std::vector<EventoBlock> model;
            {
                std::lock_guard lock(mutex);
                blocks.clear();
                for (auto& i : data) {
                    blocks.push_back(i.id);
                    model.emplace_back(i, eventList);
                    stored[i.id] = std::move(i);
                }
            }
            EventoBlockModel::getInstance()->resetModel(std::move(model));
            CalendarController::getInstance()->onLoadAllFinished();
        });

    QtConcurrent::run([=]() {
        auto f(future2);
        f.waitForFinished();
    });
}

void EventoService::load_Event(EventoID id) {
    auto future = getRepo()->getEventById(id).then([=](EventoResult<DTO_Evento> result) {
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

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
        EventoInfoController::getInstance()->onLoadFinished();
    });
}

void EventoService::load(EventoID id) {
    std::array<QFuture<bool>, 2> tasks{
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
        getRepo()->getUserParticipate(id).then([=](EventoResult<ParticipationStatus> result) {
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
    QtConcurrent::run([=]() {
        for (const auto& i : tasks)
            if (!i.result())
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
    auto future =
        getRepo()
            ->createEvent(title, description, timeConvertor(eventStart), timeConvertor(eventEnd),
                          timeConvertor(registerStart), timeConvertor(registerEnd), typeId,
                          locationId, departmentIds, tag)
            .then([=](EventoResult<bool> result) {
                if (!result) {
                    EventoEditController::getInstance()->onCreateFailure(result.message());
                    return;
                }
                EventoEditController::getInstance()->onCreateFinished();
            });

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::edit(EventoID id, const QString& title, const QString& description,
                         const QString& eventStart, const QString& eventEnd,
                         const QString& registerStart, const QString& registerEnd, int typeId,
                         int locationId, const QVariantList& departmentIds, const QString& tag) {
    auto future =
        getRepo()
            ->editEvent(id, title, description, timeConvertor(eventStart), timeConvertor(eventEnd),
                        timeConvertor(registerStart), timeConvertor(registerEnd), typeId,
                        locationId, departmentIds, tag)
            .then([=](EventoResult<bool> result) {
                if (!result) {
                    EventoEditController::getInstance()->onCreateFailure(result.message());
                    return;
                }
                EventoEditController::getInstance()->onCreateFinished();
            });
    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::getQRCode(EventoID id) {
    auto future = getRepo()->getQRCode(id).then([](EventoResult<QString> result) {
        if (!result) {
            CalendarController::getInstance()->onLoadCheckCodeFailure(result.message());
            return;
        }
        auto code = result.take();
        CalendarController::getInstance()->onLoadCheckCodeFinished(code);
    });
    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::del(EventoID id) {
    auto future = getRepo()->deleteEvent(id).then([](EventoResult<bool> result) {
        if (!result) {
            CalendarController::getInstance()->onDeleteFailure(result.message());
            return;
        }
        CalendarController::getInstance()->onDeleteFinished();
    });
    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::cancel(EventoID id) {
    auto future = getRepo()->cancelEvent(id).then([](EventoResult<bool> result) {
        if (!result) {
            CalendarController::getInstance()->onCancelFailure(result.message());
            return;
        }
        CalendarController::getInstance()->onCancelFinished();
    });
    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

void EventoService::subscribeDepartment(int departmentId, bool unsubscribe) {
    auto future =
        getRepo()
            ->subscribeDepartment(departmentId, unsubscribe)
            .then([](EventoResult<bool> result) {
                if (!result) {
                    DepartmentEventsController::getInstance()->onSubscribeFailure(result.message());
                    return;
                }
                DepartmentEventsController::getInstance()->onSubscribeFinished();
            });
    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
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

EventoBlock::EventoBlock(const DTO_Evento& src, const QVariantList& eventList)
    : id(src.id), title(src.title), time(periodConvertor(src.gmtEventStart, src.gmtEventEnd)),
      editable(eventList.contains(src.id)) {

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