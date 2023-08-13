#ifndef PLAZA_CONTROLLER_H
#define PLAZA_CONTROLLER_H

#include <QtQML>

class PlazaController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PlazaController)

public:
    explicit PlazaController(QObject *parent = nullptr) {}
};

#endif // PLAZA_CONTROLLER_H
