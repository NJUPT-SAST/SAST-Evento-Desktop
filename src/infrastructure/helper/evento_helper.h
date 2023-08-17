#ifndef EVENTOHELPER_H
#define EVENTOHELPER_H

#include <QtQml>

struct Evento;

class EventoHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER id NOTIFY idChanged)
    Q_PROPERTY(QString title MEMBER title NOTIFY titleChanged)
    Q_PROPERTY(int state MEMBER state NOTIFY stateChanged)
    Q_PROPERTY(QString eventTime MEMBER eventTime NOTIFY eventTimeChanged)
    Q_PROPERTY(
        QString registerTime MEMBER registerTime NOTIFY registerTimeChanged)
    Q_PROPERTY(QString department MEMBER department NOTIFY departmentChanged)
    Q_PROPERTY(QString location MEMBER location NOTIFY locationChanged)
    Q_PROPERTY(QString type MEMBER type NOTIFY typeChanged)
    Q_PROPERTY(QString tag MEMBER tag NOTIFY tagChanged)
    Q_PROPERTY(QString description MEMBER description NOTIFY descriptionChanged)
    Q_PROPERTY(QString buttonText MEMBER buttonText NOTIFY buttonTextChanged)

   public:
    static EventoHelper *getInstance();

    static EventoHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEvento(const Evento &evento);

   private:
    EventoHelper() = default;

    int id;
    QString title;
    int state;
    QString eventTime;
    QString registerTime;
    QString department;
    QString location;
    QString type;
    QString tag;
    QString description;
    QString buttonText;

   signals:
    void idChanged();
    void titleChanged();
    void stateChanged();
    void eventTimeChanged();
    void registerTimeChanged();
    void departmentChanged();
    void locationChanged();
    void typeChanged();
    void tagChanged();
    void descriptionChanged();
    void buttonTextChanged();
};

#endif  // EVENTOHELPER_H
