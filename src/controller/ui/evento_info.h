#ifndef EVENTO_INFO_H
#define EVENTO_INFO_H

#include <QtQml>

class Repository;

class EventoInfoController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoInfoController)

public:
    explicit EventoInfoController(QObject *parent = nullptr);
    ~EventoInfoController();
    Q_INVOKABLE void loadEventoInfo(int eventId);

signals:
    void loadEventoSuccessEvent();
    void loadEventoErrorEvent(const QString& message);

private:
    std::unique_ptr<Repository> m_repository;
};

#endif // EVENTO_INFO_H
