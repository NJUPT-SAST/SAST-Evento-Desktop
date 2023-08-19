#ifndef EVENTOHELPER_H
#define EVENTOHELPER_H

#include <QtQml>

struct Evento;

class EventoHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoHelper)
    QML_SINGLETON

    Q_PROPERTY(int id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
    Q_PROPERTY(int state MEMBER m_state NOTIFY stateChanged)
    Q_PROPERTY(QString eventTime MEMBER m_eventTime NOTIFY eventTimeChanged)
    Q_PROPERTY(QString registerTime MEMBER m_registerTime NOTIFY registerTimeChanged)
    Q_PROPERTY(QString department MEMBER m_department NOTIFY departmentChanged)
    Q_PROPERTY(QString location MEMBER m_location NOTIFY locationChanged)
    Q_PROPERTY(QString type MEMBER m_type NOTIFY typeChanged)
    Q_PROPERTY(QString tag MEMBER m_tag NOTIFY tagChanged)
    Q_PROPERTY(QString description MEMBER m_description NOTIFY descriptionChanged)
    Q_PROPERTY(bool isRegistrated MEMBER m_isRegistrated NOTIFY isRegistratedChanged)
    Q_PROPERTY(bool isParticipated MEMBER m_isParticipated NOTIFY isParticipatedChanged)
    Q_PROPERTY(bool isSubscribed MEMBER m_isSubscribed NOTIFY isSubscribedChanged)
    Q_PROPERTY(bool isfeedback MEMBER m_isfeedback NOTIFY isfeedbackChanged)

public:
    static EventoHelper *getInstance();

    static EventoHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEvento(const Evento &evento,
                      const bool isRegistrated,
                      const bool isParticipated,
                      const bool isSubscribed,
                      const bool isfeedback);

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
    bool m_isRegistrated;
    bool m_isParticipated;
    bool m_isSubscribed;
    bool m_isfeedback;

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
    void isRegistratedChanged();
    void isParticipatedChanged();
    void isSubscribedChanged();
    void isfeedbackChanged();
};

#endif  // EVENTOHELPER_H
