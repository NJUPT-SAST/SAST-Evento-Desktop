#include "gallery_helper.h"

GalleryHelper *GalleryHelper::getInstance()
{
    static GalleryHelper instance;
    return &instance;
}

GalleryHelper *GalleryHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void GalleryHelper::updateDirJson(const QString &dirJson)
{
    setProperty("dirJson", dirJson);
}

void GalleryHelper::updateDirImgInfo(const QString &dirImgInfo)
{
    setProperty("dirImgInfo", dirImgInfo);
}
