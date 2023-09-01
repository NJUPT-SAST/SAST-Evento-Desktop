#ifndef SLIDEHELPER_H
#define SLIDEHELPER_H

#include <QtQml>

struct Slide;

class SlideHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(SlideHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
    Q_PROPERTY(QString link MEMBER m_link NOTIFY linkChanged)
    Q_PROPERTY(QString url MEMBER m_url NOTIFY urlChanged)
    Q_PROPERTY(bool isEdit MEMBER m_isEdit NOTIFY isEditChange)

public:
    static SlideHelper *getInstance();

    static SlideHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateSlide(const int &slideId, const QString &title, const QString &link, const QString &url);

private:
    SlideHelper() = default;

    int m_id;
    QString m_title;
    QString m_link;
    QString m_url;
    bool m_isEdit;

signals:
    void idChanged();
    void titleChanged();
    void linkChanged();
    void urlChanged();
    void isEditChange();
};

#endif // SLIDEHELPER_H
