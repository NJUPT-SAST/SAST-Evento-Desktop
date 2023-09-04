#include "gallery.h"

QString GalleryController::loadGalleryUrlList()
{
    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /          about throw error            /
    /                                       /
    /                                       /
    /--------------------------------------*/
    int err = 0;
    if(err == 1){
        emit loadGalleryUrlListErrorEvent("url list error");
        return QString();
    }

    QString galleryUrlList = "[{\"id\":1,\"name\":\"default\"},{\"id\":2,\"name\":\"1st dir\"},{\"id\":3,\"name\":\"2nd dir\"},{\"id\":4,\"name\":\"1st dir\"},{\"id\":5,\"name\":\"2nd dir\"},{\"id\":6,\"name\":\"1st dir\"},{\"id\":7,\"name\":\"2nd dir\"}]";

    emit loadGalleryUrlListSuccessEvent();
    return galleryUrlList;
}

GalleryController *GalleryController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new GalleryController();
}
