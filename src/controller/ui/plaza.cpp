#include <QDesktopServices>
#include "plaza.h"
#include "convertor.h"
#include "latest_evento_model.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"

void PlazaController::loadPlazaInfo() {
    EventoException err;
    auto slides = getRepo()->get_home_slide_list(3, err);
    if (slides.empty()) {
        slides.emplace_back(
            DTO_Slide{0, "SAST Evento", "", "qrc:/res/image/banner_1.png"});
        slides.emplace_back(
            DTO_Slide{0, "SAST C++", "", "qrc:/res/image/banner_2.png"});
        slides.emplace_back(
            DTO_Slide{0, "SAST", "", "qrc:/res/image/banner_3.png"});
    } else if (slides.size() == 1) {
        slides.emplace_back(
            DTO_Slide{0, "SAST C++", "", "qrc:/res/image/banner_2.png"});
        slides.emplace_back(
            DTO_Slide{0, "SAST", "", "qrc:/res/image/banner_3.png"});
    } else if (slides.size() == 2) {
        slides.emplace_back(
            DTO_Slide{0, "SAST", "", "qrc:/res/image/banner_3.png"});
    }
    SlideModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(slides));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    UndertakingEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<UndertakingEvento>>()(
            getRepo()->get_undertaking_list(err)));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    LatestEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<LatestEvento>>()(
            getRepo()->get_latest_list(err)));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    emit loadPlazaSuccessEvent();
}

void PlazaController::openUrl(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

PlazaController *PlazaController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new PlazaController();
}
