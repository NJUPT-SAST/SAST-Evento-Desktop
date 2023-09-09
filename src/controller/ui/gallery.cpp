#include "gallery.h"
#include "gallery_helper.h"

void GalleryController::loadGalleryDirJson()
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
        GalleryHelper::getInstance()->updateDirJson(QString());
        return;
    }

    QString galleryUrlList = "[{\"id\":1,\"name\":\"default\"},{\"id\":2,\"name\":\"1st dir\"},{\"id\":3,\"name\":\"2nd dir\"}]";

    emit loadGalleryUrlListSuccessEvent();
    GalleryHelper::getInstance()->updateDirJson(galleryUrlList);
    return;
}

void GalleryController::loadGalleryDirImgInfo(const QString& dirName, const int pageNumber){
    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /          about throw error            /
    /                                       /
    /                                       /
    /--------------------------------------*/
    int err = 0;
    //static int a = 0;
    //if(a == 0 && (pageNumber == 3 || pageNumber == 4)){
    //    err = 1;
    //    a = 1;
    //}
    if(err == 1){
        emit loadGalleryDirImgInfoErrorEvent("Dir Img Info error");
        GalleryHelper::getInstance()->updateDirImgInfo(QString());
        return;
    }

    int num;
    if(dirName == "default"){
        num = 1;
    }else if(dirName == "1st dir"){
        num = 2;
    }else if(dirName == "2nd dir"){
        num = 3;
    }
    int pageItemCount = 120 + 20 * num;
    QString imgJson = "[\"qrc:/res/image/ic_home_github.png\",\"qrc:/res/image/banner_3.png\",\"qrc:/res/image/banner_2.png\",\"qrc:/res/image/banner_1.png\"]";
    QString galleryDirImgInfo = "{\"count\":\"" + QString::number(pageItemCount) + "\",\"url\":" + imgJson + "}";


    emit loadGalleryDirImgInfoSuccessEvent();
    GalleryHelper::getInstance()->updateDirImgInfo(galleryDirImgInfo);
    return;
}

void GalleryController::deleteImgRequest(const QString& url){
    int err = 0;
    if(err == 1){
        emit deleteImgRequestErrorEvent("url delete error" + url);
        return;
    }

    emit deleteImgRequestSuccessEvent();
    return;
}

GalleryController *GalleryController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new GalleryController();
}
