#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

#include <QtQml>

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadEditInfo(int eventId = 0);
    Q_INVOKABLE void createEvento(const QString& title,
                                  const QString& description,
                                  const QString& eventStart,
                                  const QString& eventEnd,
                                  const QString& registerStart,
                                  const QString& registerEnd,
                                  int typeId,
                                  int loactionId,
                                  const QVariantList& departmentId,
                                  const QString& tag);

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
