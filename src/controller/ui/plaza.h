#ifndef PLAZA_CONTROLLER_H
#define PLAZA_CONTROLLER_H

#include <QtQml>

class Repository;

class PlazaController : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(PlazaController)

public:
    Q_INVOKABLE void loadPlazaInfo();

signals:
    void loadPlazaSuccessEvent();
    void loadPlazaErrorEvent(const QString& message);
    
public:
    PlazaController() = default;
    ~PlazaController() = default;
};

#endif // PLAZA_CONTROLLER_H
