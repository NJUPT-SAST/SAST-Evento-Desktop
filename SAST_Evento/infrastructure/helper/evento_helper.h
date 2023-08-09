#ifndef EVENTOHELPER_H
#define EVENTOHELPER_H

#include <QObject>
#include <QtQml/qqml.h>
#include "domain/entity/evento.h"
#include "stdafx.h"
#include "infrastructure/util/util.hpp"

class EventoHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,id)
    Q_PROPERTY_AUTO(QString,title)
    Q_PROPERTY_AUTO(QString,description)
    Q_PROPERTY_AUTO(QString,time)
    Q_PROPERTY_AUTO(QString,type)
    Q_PROPERTY_AUTO(QString,location)
    Q_PROPERTY_AUTO(QString,tag)
    Q_PROPERTY_AUTO(int,participate)
    Q_PROPERTY_AUTO(int,checked)
    QML_NAMED_ELEMENT(EventoHelper)
    QML_SINGLETON

private:
    explicit EventoHelper(QObject *parent = nullptr);
    static EventoHelper* m_instance;

public:
    static EventoHelper* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    static EventoHelper* getInstance();

    void updateEvento(const Evento& evento) {
        id(evento.id);
        title(evento.title);
        description(evento.description);
        time(evento.time);
        type(evento.type);
        location(evento.location);
        tag(evento.tag);
        participate(toUType(evento.participate));
        checked(toUType(evento.checked));
    }
};

#endif // EVENTOHELPER_H
