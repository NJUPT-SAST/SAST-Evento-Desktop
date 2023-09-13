#include <QDesktopServices>
#include "plaza.h"
#include "convertor.h"
#include "latest_evento_model.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"

void PlazaController::loadPlazaInfo() {
    EventoException err;
    auto slides = getRepo()->getHomeSlideList(3, err);
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

    if (err) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    auto future = getRepo()->getUndertakingList();
    future.waitForFinished();
    auto result = future.takeResult();
    if (!result) {
        emit loadPlazaErrorEvent(result.message());
        return;
    }
    UndertakingEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<UndertakingEvento>>()(result.take()));

    future = getRepo()->getLatestList();
    future.waitForFinished();
    result = future.takeResult();
    LatestEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>, std::vector<LatestEvento>>()(result.take()));

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
