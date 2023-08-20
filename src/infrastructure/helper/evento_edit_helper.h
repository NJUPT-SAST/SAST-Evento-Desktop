#ifndef EVENTOEDITHELPER_H
#define EVENTOEDITHELPER_H

#include <QtQml>

class EventoEditHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditHelper)
    QML_SINGLETON


    //Q_PROPERTY(QString id MEMBER id NOTIFY idChanged)


public:
    static EventoEditHelper *getInstance();

    static EventoEditHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    //void updateEventoEdit(const QString &eventoJson);

    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /                                       /
    /                                       /
    /--------------------------------------*/

private:
    EventoEditHelper() = default;

    //QString eventoJson;

    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /                                       /
    /                                       /
    /--------------------------------------*/

signals:
    //void eventoJsonChanged();

    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /                                       /
    /                                       /
    /--------------------------------------*/
};

#endif // EVENTOEDITHELPER_H
