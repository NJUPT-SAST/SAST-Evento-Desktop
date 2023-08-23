#include "slide_management.h"

void SlideManagementController::loadAllSlide()
{

}

SlideManagementController *SlideManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new SlideManagementController();
}
