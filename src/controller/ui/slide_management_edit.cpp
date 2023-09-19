#include "slide_management_edit.h"
#include "slide_helper.h"

// deprecated

void SlideManagementEditController::loadEditInfo(const int &slideId, const bool &isEdit)
{
    if(isEdit) {
        if(slideId != 0){
            return emit loadEditSuccessEvent();
        }
        else {
            return emit loadEditErrorEvent("no slide");
        }
    }
    else {
        SlideHelper::getInstance()->updateSlide(0, "", "", "");
        return emit loadEditSuccessEvent();
    }
}

void SlideManagementEditController::createSlide(const QString &title, const QString &link, const QString &url)
{
    // TODO 创建幻灯片
    return emit createSuccessEvent();
}

void SlideManagementEditController::updateSlide(const QString &title, const QString &link, const QString &url)
{
    // TODO 更改幻灯片
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
