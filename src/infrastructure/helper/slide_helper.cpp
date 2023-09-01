#include "slide_helper.h"

SlideHelper *SlideHelper::getInstance()
{
    static SlideHelper instance;
    return &instance;
}

SlideHelper *SlideHelper::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

void SlideHelper::updateSlide(const int &slideId, const QString &title, const QString &link, const QString &url)
{
    setProperty("id", slideId);
    setProperty("title", title);
    setProperty("link", link);
    setProperty("url", url);
}
