#ifndef EVENTOHELPER_H
#define EVENTOHELPER_H

#include <QtQml>
#include "types.h"

class Evento;

class EventoHelper: public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString title MEMBER m_title)
    Q_PROPERTY(int state MEMBER m_state)
    Q_PROPERTY(QString eventTime MEMBER m_eventTime)
    Q_PROPERTY(QString registerTime MEMBER m_registerTime)
    Q_PROPERTY(QString department MEMBER m_department)
    Q_PROPERTY(QString location MEMBER m_location)
    Q_PROPERTY(QString type MEMBER m_type)
    Q_PROPERTY(QString tag MEMBER m_tag)
    Q_PROPERTY(QString description MEMBER m_description)
    Q_PROPERTY(QString buttonText MEMBER m_buttonText)

public:
    static EventoHelper* getInstance();

    static EventoHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEvento(const Evento& evento);

private:
    EventoHelper() = default;

    int m_id;
    QString m_title;
    int m_state;
    QString m_eventTime;
    QString m_registerTime;
    QString m_department;
    QString m_location;
    QString m_type;
    QString m_tag;
    QString m_description;
    QString m_buttonText;
};

#endif // EVENTOHELPER_H
