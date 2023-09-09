#ifndef GALLERY_CONTROLLER_H
#define GALLERY_CONTROLLER_H

#include <QtQml>

class GalleryController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(GalleryController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadGalleryDirJson();
    Q_INVOKABLE void loadGalleryDirImgInfo(const QString& dirName, const int pageNumber);
    Q_INVOKABLE void deleteImgRequest(const QString& url);

signals:
    void loadGalleryUrlListSuccessEvent();
    void loadGalleryUrlListErrorEvent(const QString &message);

    void loadGalleryDirImgInfoSuccessEvent();
    void loadGalleryDirImgInfoErrorEvent(const QString &message);

    void deleteImgRequestSuccessEvent();
    void deleteImgRequestErrorEvent(const QString &message);


public:
    GalleryController() = default;
    static GalleryController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // GALLERY_CONTROLLER_H
