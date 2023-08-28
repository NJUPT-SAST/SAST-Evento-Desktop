#ifndef SLIDE_MANAGEMENT_EDIT_H
#define SLIDE_MANAGEMENT_EDIT_H

#include <QtQml>

class SlideManagementEditController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(SlideManagementEditController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadEditInfo(const int &slideId, const bool &isEdit);
    Q_INVOKABLE void createSlide(const QString &title, const QString &link, const QString &url);
    Q_INVOKABLE void updateSlide(const QString &title, const QString &link, const QString &url);
    Q_INVOKABLE void onClickSubmit(const QString &title, const QString &link, const QString &url, const bool &isEdit);

signals:
    void loadEditSuccessEvent();
    void loadEditErrorEvent(const QString& messge);

    void createSuccessEvent();
    void createErrorEvent(const QString &message);

    void updateSuccessEvent();
    void updateErrorEvent(const QString &message);

public:
    static SlideManagementEditController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    SlideManagementEditController() = default;
};

#endif // SLIDE_MANAGEMENT_EDIT_H
