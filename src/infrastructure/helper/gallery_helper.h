#ifndef GALLERYHELPER_H
#define GALLERYHELPER_H

#include <QtQml>

class GalleryHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(GalleryHelper)
    QML_SINGLETON

    Q_PROPERTY(int maxNum MEMBER m_maxNum NOTIFY maxNumChanged)
    Q_PROPERTY(QString dirJson MEMBER m_dirJson NOTIFY dirJsonChanged)
    Q_PROPERTY(QVariantList urlList MEMBER m_urlList NOTIFY urlListChanged)
    Q_PROPERTY(QString dirImgInfo MEMBER m_dirImgInfo NOTIFY dirImgInfoChanged)

public:
    static GalleryHelper *getInstance();

    static GalleryHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateDirJson(const QString &dirJson);
    void updateDirImgInfo(const QString &dirImgInfo);

private:
    GalleryHelper() = default;

    int m_maxNum;
    QString m_dirJson;
    QVariantList m_urlList;
    QString m_dirImgInfo;

signals:
    void maxNumChanged();
    void dirJsonChanged();
    void urlListChanged();
    void dirImgInfoChanged();
};


#endif // GALLERYHELPER_H
