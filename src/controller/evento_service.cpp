#include "evento_service.h"
#include "convertor.h"
#include "evento.h"
#include "repository.h"
#include "plaza.h"
#include "latest_evento_model.h"
#include "undertaking_evento_model.h"
#include "evento_info.h"
#include "evento_helper.h"

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
			mutex.lock();
			undertaking.clear();
			for (auto& i : data) {
				undertaking.push_back(i.id);
				model.push_back(Convertor<DTO_Evento, UndertakingEvento>()(i));
				stored[i.id] = std::move(i);
			}
			mutex.unlock();
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
			mutex.lock();
			latest.clear();
			for (auto& i : data) {
				undertaking.push_back(i.id);
				model.push_back(Convertor<DTO_Evento, LatestEvento>()(i));
				stored[i.id] = std::move(i);
			}
			mutex.unlock();
			LatestEventoModel::getInstance()->resetModel(std::move(model));
			return true;
		})
	};
	QtConcurrent::run([=]() {
		for (const auto& i : tasks)
			if (!i.result())
				return;
		PlazaController::getInstance()->onPlazaLoadFinished();
	});
}

Evento::Evento(const DTO_Evento& src) : id(src.id), title(src.title), description(src.description), type(src.type), location(src.location), tag(src.tag), state(src.state) {
	for (const auto& i : src.departments) {
		this->department.push_back(i.name);
		this->department.push_back('\n');
	}
	this->eventStart = src.gmtEventStart.toString("yyyy年MM月dd日 HH:mm:ss");
	this->eventEnd = src.gmtEventEnd.toString("yyyy年MM月dd日 HH:mm:ss");
	this->registrationStart = src.gmtRegistrationStart.toString("yyyy年MM月dd日 HH:mm:ss");
	this->registrationEnd = src.gmtRegistrationEnd.toString("yyyy年MM月dd日 HH:mm:ss");
}

void EventoService::load(EventoID id) {
	getRepo()->getEventById(id).then([=](EventoResult<DTO_Evento> result) {
		if (!result)
			EventoInfoController::getInstance()->onLoadFailure(result.message());
		mutex.lock();
		Evento event = (stored[id] = std::move(result.take()));
		mutex.unlock();
		if (EventoHelper::getInstance()->update(event))
			EventoInfoController::getInstance()->onLoadSuccess();
		});
}

DTO_Evento EventoService::edit(EventoID id) {
	std::shared_lock guard(mutex);
	return stored[id];
}
