#include <QDesktopServices>
#include "plaza.h"
#include "repository.h"
#include "slide_model.h"
#include "evento_service.h"
#include "slide_service.h"
#include "slide.h"

void PlazaController::loadPlazaInfo() {
    EventoException err;
//    auto slides = getRepo()->getHomeSlideList(3, err);
//    if (slides.empty()) {
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST Evento", "", "qrc:/res/image/banner_1.png"});
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST C++", "", "qrc:/res/image/banner_2.png"});
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST", "", "qrc:/res/image/banner_3.png"});
//    } else if (slides.size() == 1) {
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST C++", "", "qrc:/res/image/banner_2.png"});
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST", "", "qrc:/res/image/banner_3.png"});
//    } else if (slides.size() == 2) {
//        slides.emplace_back(
//            DTO_Slide{0, 0, "SAST", "", "qrc:/res/image/banner_3.png"});
//    }
//    std::vector<Slide> model;
//    for (const auto& i : slides) {
//        model.push_back(Slide(i));
//    }
//    SlideModel::getInstance()->resetModel(model);
    EventoService::getInstance().load_Plaza();
    if (err)
        emit loadPlazaErrorEvent(err.message());
}

void PlazaController::openUrl(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

PlazaController *PlazaController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

PlazaController *PlazaController::getInstance()
{
    static PlazaController instance;
    return &instance;
}
