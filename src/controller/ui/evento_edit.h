#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

#include <QtQml>

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadEditInfo(int eventId = 0);
    Q_INVOKABLE void createEvento(QString title,
                                  QString description,
                                  QString eventStart,
                                  QString eventEnd,
                                  QString registerStart,
                                  QString registerEnd,
                                  int typeId,
                                  int loactionId,
                                  QVariantList departmentId,
                                  QString tag,
                                  QVariantList urlList);

signals:
    void loadEditSuccessEvent();
    void loadEditErrorEvent(const QString messge);

    void createSuccessEvent();
    void createErrorEvent(const QString message);

public:
    static EventoEditController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    EventoEditController() = default;
};

#endif // EVENTO_EDIT_CONTROLLER_H
