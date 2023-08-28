#ifndef SLIDE_MANAGEMENT_H
#define SLIDE_MANAGEMENT_H

#include <QtQml>

class SlideManagementController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(SlideManagementController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadAllSlide();
    Q_INVOKABLE void deleteSlide(const int slideId);

signals:
    void loadAllSlideSuccess();
    void loadAllSlideError(const QString &message);

    void deleteSlideSuccess();
    void deleteSlideError(const QString &message);

public:
    SlideManagementController() = default;
    static SlideManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // SLIDE_MANAGEMENT_H
