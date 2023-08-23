#ifndef EVENTOEDITHELPER_H
#define EVENTOEDITHELPER_H

#include <QtQml>
#include "dto/evento.h"

class EventoEditHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditHelper)
    QML_SINGLETON

    Q_PROPERTY(QString departmentJson MEMBER m_departmentJson NOTIFY departmentJsonChanged)
    Q_PROPERTY(QString locationJson MEMBER m_locationJson NOTIFY locationJsonChanged)
    Q_PROPERTY(QString typeJson MEMBER m_typeJson NOTIFY typeJsonChanged)
    Q_PROPERTY(QVariantList departmentIds MEMBER m_departmentIds NOTIFY departmentIdsChanged)
    Q_PROPERTY(int locationId MEMBER m_locationId NOTIFY locationIdChanged)
    Q_PROPERTY(int typeId MEMBER m_typeId NOTIFY typeIdChanged)
    Q_PROPERTY(bool allowConflict MEMBER m_allowConflict NOTIFY allowConflictChanged)

public:
    static EventoEditHelper *getInstance();

    static EventoEditHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEventoEdit(const QString& departmentJson, const QString& m_locationJson,
                          const QString& m_typeJson, const DTO_Evento& evento = DTO_Evento());

private:
    EventoEditHelper() = default;

    QString m_departmentJson;
    QString m_locationJson;
    QString m_typeJson;

    QVariantList m_departmentIds;
    int m_locationId;
    int m_typeId;
    bool m_allowConflict;

signals:
    void departmentJsonChanged();
    void locationJsonChanged();
    void typeJsonChanged();
    void departmentIdsChanged();
    void locationIdChanged();
    void typeIdChanged();
    void allowConflictChanged();
};

#endif // EVENTOEDITHELPER_H
