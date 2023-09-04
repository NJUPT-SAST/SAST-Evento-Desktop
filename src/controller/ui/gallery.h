#ifndef GALLERY_CONTROLLER_H
#define GALLERY_CONTROLLER_H

#include <QtQml>

class GalleryController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(GalleryController)
    QML_SINGLETON

public:
    Q_INVOKABLE QString loadGalleryUrlList();
    //Q_INVOKABLE void loadGalleryDirInfo();

signals:
    void loadGalleryUrlListSuccessEvent();
    void loadGalleryUrlListErrorEvent(const QString &message);

public:
    GalleryController() = default;
    static GalleryController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // GALLERY_CONTROLLER_H
