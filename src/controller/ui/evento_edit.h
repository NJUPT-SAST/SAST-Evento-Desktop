#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

 #include <QtQml>

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)
    QML_SINGLETON

public:
    explicit EventoEditController(QObject *parent = nullptr) {}
    static EventoEditController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_EDIT_CONTROLLER_H
