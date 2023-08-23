#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

#include <QtQml>

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadEditInfo(int eventId = 0);

signals:
    void loadEditSuccessEvent();
    void loadEditErrorEvent(const QString& messge);

public:
    static EventoEditController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    EventoEditController() = default;
};

#endif // EVENTO_EDIT_CONTROLLER_H
