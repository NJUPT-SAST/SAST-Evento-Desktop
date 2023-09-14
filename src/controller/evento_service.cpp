#include "evento_service.h"
#include "convertor.h"
#include "repository.h"
#include "plaza.h"
#include "latest_evento_model.h"
#include "undertaking_evento_model.h"

#include <QtConcurrent>

void EventoService::load_Plaza() {
    QtConcurrent::run([this]() {
        auto future1 = getRepo()->getUndertakingList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result)
                return PlazaController::getInstance()->onPlazaLoadFailure(result);
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
        });
        auto future2 = getRepo()->getLatestList().then([this](EventoResult<std::vector<DTO_Evento>> result) {
            if (!result)
                return PlazaController::getInstance()->onPlazaLoadFailure(result);
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
        });
        future1.waitForFinished();
        future2.waitForFinished();
    }).then([]() {
        PlazaController::getInstance()->onPlazaLoadFinished();
    });
}
