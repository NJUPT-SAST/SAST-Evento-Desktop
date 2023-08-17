#ifndef PLAZA_CONTROLLER_H
#define PLAZA_CONTROLLER_H

#include <QtQml>
#include "repository.h"

class PlazaController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PlazaController)

public:
    explicit PlazaController(QObject *parent = nullptr);
    Q_INVOKABLE void loadPlazaInfo();

signals:
    void loadPlazaSuccessEvent();
    void loadPlazaErrorEvent(const QString& message);

private:
    std::unique_ptr<Repository> m_repository;
};

#endif // PLAZA_CONTROLLER_H
