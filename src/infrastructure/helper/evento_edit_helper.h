#ifndef EVENTOEDITHELPER_H
#define EVENTOEDITHELPER_H

#include <QtQml>
#include "dto/evento.h"

class EventoEditHelper : public QObject
{
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
    Q_PROPERTY(bool isEdited MEMBER m_isEdited NOTIFY isEditedChanged)
    Q_PROPERTY(QString eventDateStart MEMBER m_eventDateStart NOTIFY eventDateStartChanged)
    Q_PROPERTY(QString eventTimeStartH MEMBER m_eventTimeStartH NOTIFY eventTimeStartHChanged)
    Q_PROPERTY(QString eventTimeStartM MEMBER m_eventTimeStartM NOTIFY eventTimeStartMChanged)
    Q_PROPERTY(QString eventDateEnd MEMBER m_eventDateEnd NOTIFY eventDateEndChanged)
    Q_PROPERTY(QString eventTimeEndH MEMBER m_eventTimeEndH NOTIFY eventTimeEndHChanged)
    Q_PROPERTY(QString eventTimeEndM MEMBER m_eventTimeEndM NOTIFY eventTimeEndMChanged)
    Q_PROPERTY(QString registerDateStart MEMBER m_registerDateStart NOTIFY registerDateStartChanged)
    Q_PROPERTY(QString registerTimeStartH MEMBER m_registerTimeStartH NOTIFY registerTimeStartHChanged)
    Q_PROPERTY(QString registerTimeStartM MEMBER m_registerTimeStartM NOTIFY registerTimeStartMChanged)
    Q_PROPERTY(QString registerDateEnd MEMBER m_registerDateEnd NOTIFY registerDateEndChanged)
    Q_PROPERTY(QString registerTimeEndH MEMBER m_registerTimeEndH NOTIFY registerTimeEndHChanged)
    Q_PROPERTY(QString registerTimeEndM MEMBER m_registerTimeEndM NOTIFY registerTimeEndMChanged)

public:
    static EventoEditHelper *getInstance();

    static EventoEditHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEventoEdit(const QString &departmentJson, const QString &m_locationJson,
                          const QString &m_typeJson, const DTO_Evento &evento = DTO_Evento());

private:
    EventoEditHelper() = default;

    QString m_departmentJson;
    QString m_locationJson;
    QString m_typeJson;
    bool m_isEdited; // true: 编辑模式 false: 创建模式

    // 编辑模式属性
    QVariantList m_departmentIds;
    QString m_eventDateStart;
    QString m_eventTimeStartH;
    QString m_eventTimeStartM;
    QString m_eventDateEnd;
    QString m_eventTimeEndH;
    QString m_eventTimeEndM;
    QString m_registerDateStart;
    QString m_registerTimeStartH;
    QString m_registerTimeStartM;
    QString m_registerDateEnd;
    QString m_registerTimeEndH;
    QString m_registerTimeEndM;
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
    void isEditedChanged();
    void eventDateStartChanged();
    void eventTimeStartHChanged();
    void eventTimeStartMChanged();
    void eventDateEndChanged();
    void eventTimeEndHChanged();
    void eventTimeEndMChanged();
    void registerDateStartChanged();
    void registerTimeStartHChanged();
    void registerTimeStartMChanged();
    void registerDateEndChanged();
    void registerTimeEndHChanged();
    void registerTimeEndMChanged();
};

#endif // EVENTOEDITHELPER_H
