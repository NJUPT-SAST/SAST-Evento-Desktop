#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

 #include <QtQml>

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)

public:
    explicit EventoEditController(QObject *parent = nullptr) {}
};

#endif // EVENTO_EDIT_CONTROLLER_H
