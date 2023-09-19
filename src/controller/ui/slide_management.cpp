#include "slide_management.h"
#include "slide_model.h"
#include "repository.h"

// deprecated

void SlideManagementController::loadAllSlide()
{
    return emit loadAllSlideSuccess();
}

void SlideManagementController::deleteSlide(const int slideId)
{
    SlideModel::getInstance()->removeById(slideId);

    // TODO 请求删除部分
    return emit deleteSlideSuccess();
}

SlideManagementController *SlideManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new SlideManagementController();
}
