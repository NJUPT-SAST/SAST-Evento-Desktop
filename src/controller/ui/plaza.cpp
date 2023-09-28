#include "plaza.h"
#include "evento_service.h"
#include "slide_service.h"

#include <QDesktopServices>

void PlazaController::loadPlazaInfo()
{
    SlideService::getInstance().load_HomeSlide(3);
    EventoService::getInstance().load_Plaza();
}

void PlazaController::loadHomeSlide()
{
    SlideService::getInstance().load_HomeSlide(3);
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
