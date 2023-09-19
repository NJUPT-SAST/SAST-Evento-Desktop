#include "evento_service.h"
#include "convertor.h"
#include "evento.h"
#include "repository.h"
#include "plaza.h"
#include "latest_evento_model.h"
#include "undertaking_evento_model.h"
#include "evento_info.h"
#include "evento_helper.h"
#include "schedule.h"
#include "scheduled_evento_model.h"

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
		})
	};
    QtConcurrent::run([=] {
		for (const auto& i : tasks)
			if (!i.result())
				return;
        PlazaController::getInstance()->onPlazaLoadFinished();
    });
}

void EventoService::load_RegisteredSchedule()
{
    getRepo()->getRegisteredList().then([=](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            ScheduleController::getInstance()->onLoadRegisteredFailure(result.message());
            return false;
        }
        auto data = result.take();
        std::vector<Schedule> model;
        {
            std::lock_guard lock(mutex);
            registered.clear();
            for(auto& i : data) {
                registered.push_back(i.id);
                model.push_back(Schedule(i));
                stored[i.id] = std::move(i);
            }
        }
        ScheduledEventoModel::getInstance()->resetModel(std::move(model));
        return true;
    });
    QtConcurrent::run([] {
        ScheduleController::getInstance()->onLoadRegisteredFinished();
    });
}

void EventoService::load_SubscribedSchedule()
{
    getRepo()->getSubscribedList().then([=](EventoResult<std::vector<DTO_Evento>> result) {
        if (!result) {
            ScheduleController::getInstance()->onLoadSubscribedFailure(result.message());
            return false;
        }
        auto data = result.take();
        std::vector<Schedule> model;
        {
            std::lock_guard lock(mutex);
            subscribed.clear();
            for(auto& i : data) {
                subscribed.push_back(i.id);
                model.push_back(Schedule(i));
                stored[i.id] = std::move(i);
            }
        }
        ScheduledEventoModel::getInstance()->resetModel(std::move(model));
        return true;
    });
    QtConcurrent::run([] {
        ScheduleController::getInstance()->onLoadSubscribedFinished();
    });
}

void EventoService::load(EventoID id) {
	getRepo()->getEventById(id).then([=](EventoResult<DTO_Evento> result) {
		if (!result)
            EventoInfoController::getInstance()->onLoadFailure(result.message());
        mutex.lock();
        Evento event = (stored[id] = std::move(result.take()));
        mutex.unlock();
		if (EventoHelper::getInstance()->update(event))
            EventoInfoController::getInstance()->onLoadFinished();
        });
}

DTO_Evento EventoService::edit(EventoID id) {
	std::shared_lock guard(mutex);
	return stored[id];
}

Evento::Evento(const DTO_Evento& src) : id(src.id), title(src.title), description(src.description), type(src.type), location(src.location), tag(src.tag), state(src.state) {
    this->department = departmentConvertor(src.departments);
    this->eventStart = src.gmtEventStart.toString("yyyy年MM月dd日 HH:mm:ss");
    this->eventEnd = src.gmtEventEnd.toString("yyyy年MM月dd日 HH:mm:ss");
    this->registrationStart = src.gmtRegistrationStart.toString("yyyy年MM月dd日 HH:mm:ss");
    this->registrationEnd = src.gmtRegistrationEnd.toString("yyyy年MM月dd日 HH:mm:ss");
}

Schedule::Schedule(const DTO_Evento& src) : id(src.id), title(src.title), state(src.state), location(src.location) {
    this->department = departmentConvertor(src.departments);
    this->date = src.gmtEventStart.toString(QStringLiteral("MM月dd日"));
    this->startTime = src.gmtEventStart.toString(QStringLiteral("hh:mm"));
    this->endTime = src.gmtEventEnd.toString(QStringLiteral("hh:mm"));
}

UndertakingEvento::UndertakingEvento(const DTO_Evento& src) : id(src.id), title(src.title), location(src.location) {
    this->time = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->department = departmentConvertor(src.departments);
}

LatestEvento::LatestEvento(const DTO_Evento& src) : id(src.id), title(src.title), description(src.description) {
    this->time = periodConvertor(src.gmtEventStart, src.gmtEventEnd);
    this->department = departmentConvertor(src.departments);
}
