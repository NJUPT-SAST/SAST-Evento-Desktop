#include "slide_service.h"
#include "image.h"
#include "plaza.h"
#include "repository.h"
#include "slide_model.h"

Slide::Slide(const DTO_Slide& src) : id(src.id), title(src.title), link(src.link), url(src.url) {}

void SlideService::load_HomeSlide(const int size) {
    getRepo()->getHomeSlideList(size).then([this](EventoResult<std::vector<DTO_Slide>> result) {
        if (!result) {
            PlazaController::getInstance()->onHomeSlideLoadFailure(result.message());
            return;
        }
        auto data = result.take();
        std::vector<Slide> model;
        {
            std::lock_guard lock(mutex);
            slides.clear();
            for (auto& i : data) {
                slides.emplace_back(i);
                model.emplace_back(i);
            }
        }
        SlideModel::getInstance()->resetModel(std::move(ImageManagement::fillSlideList(model)));
        PlazaController::getInstance()->onHomeSlideLoadFinished();
    });
}
