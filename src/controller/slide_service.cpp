#include "slide_service.h"
#include "slide_model.h"
#include "dto/slide.h"
#include "plaza.h"
#include "repository.h"
#include <QtConcurrent>

Slide::Slide(const DTO_Slide& src) : id(src.id), title(src.title), link(src.link), url(src.url) {}

void SlideService::load_HomeSlide(const int size)
{
    auto future = getRepo()->getHomeSlideList(size).then([=](EventoResult<std::vector<DTO_Slide>> result) {
        if (!result) {
            PlazaController::getInstance()->onHomeSlideLoadFailure(result.message());
            return;
        }
        auto data = result.take();
        std::vector<Slide> model;
        {
            std::lock_guard lock(mutex);
            slides.clear();
            for(auto& i : data) {
                slides.push_back(Slide(i));
                model.push_back(Slide(i));
            }
        }
        SlideModel::getInstance()->resetModel(std::move(model));
    });

    QtConcurrent::run([=] {
        auto f(future);
        f.waitForFinished();
        PlazaController::getInstance()->onHomeSlideLoadFinished();
    });
}
