#include "slide_management.h"
#include "convertor.h"
#include "slide_model.h"
#include "repository.h"

void SlideManagementController::loadAllSlide()
{
    EventoException err;
    SlideModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Slide>, std::vector<Slide>>()(
            getRepo()->get_home_slide_list(3, err)));
    // get_home_slide_list 参数更改为size和page（未来替换）
    if((int)err.code())
        return emit loadAllSlideError(err.message());
    return emit loadAllSlideSuccess();
}

void SlideManagementController::deleteSlide(const int slideId)
{
    return emit deleteSlideSuccess();
}

SlideManagementController *SlideManagementController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new SlideManagementController();
}
