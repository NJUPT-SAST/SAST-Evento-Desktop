#include "slide_management_edit.h"
#include "evento_exception.h"

void SlideManagementEditController::loadEditInfo(int slideId)
{
    EventoException err;
    if(slideId != 0){
        if((int)err.code())
            return emit loadEditErrorEvent(err.message());
    }
    else {
        return emit loadEditErrorEvent("no slide");
    }
    return emit loadEditSuccessEvent();
}

void SlideManagementEditController::createSlide(const QString &title, const QString &link, const QString &url)
{
    return emit createSuccessEvent();
}

void SlideManagementEditController::updateSlide(const QString &title, const QString &link, const QString &url)
{
    return emit updateSuccessEvent();
}

void SlideManagementEditController::onClickSubmit(const QString &title, const QString &link, const QString &url, const bool &isEdit)
{
    if(isEdit){
        updateSlide(title, link, url);
    }
    else {
        createSlide(title, link, url);
    }
}

SlideManagementEditController *SlideManagementEditController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new SlideManagementEditController();
}
