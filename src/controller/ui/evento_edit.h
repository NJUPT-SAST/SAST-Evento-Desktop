#ifndef EVENTO_EDIT_CONTROLLER_H
#define EVENTO_EDIT_CONTROLLER_H

#include <QtQml>

#include "types.h"

class DTO_Evento;

class EventoEditController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditController)
    QML_SINGLETON

    Q_PROPERTY(QString departmentJson MEMBER m_departmentJson NOTIFY departmentJsonChanged)
    Q_PROPERTY(QString locationJson MEMBER m_locationJson NOTIFY locationJsonChanged)
    Q_PROPERTY(QString typeJson MEMBER m_typeJson NOTIFY typeJsonChanged)
    Q_PROPERTY(int typeId MEMBER m_typeId NOTIFY typeIdChanged)
    Q_PROPERTY(bool allowConflict MEMBER m_allowConflict NOTIFY allowConflictChanged)
    Q_PROPERTY(bool isEditMode MEMBER m_isEditMode NOTIFY isEditModeChanged)
    Q_PROPERTY(QString eventStart MEMBER m_eventStart NOTIFY eventStartChanged)
    Q_PROPERTY(QString eventEnd MEMBER m_eventEnd NOTIFY eventEndChanged)
    Q_PROPERTY(QString registerStart MEMBER m_registerStart NOTIFY registerStartChanged)
    Q_PROPERTY(QString registerEnd MEMBER m_registerEnd NOTIFY registerEndChanged)

public:
    Q_INVOKABLE void loadEditInfo();
    Q_INVOKABLE void editEvento(EventoID id);

private:
    QString m_departmentJson;
    QString m_locationJson;
    QString m_typeJson;
    bool m_isEditMode; // true: 编辑模式 false: 创建模式
    // 编辑模式属性
    int m_typeId;
    bool m_allowConflict;
    QString m_eventStart;
    QString m_eventEnd;
    QString m_registerStart;
    QString m_registerEnd;

    void preload();

signals:
    void loadEditSuccessEvent();
    void loadEditErrorEvent(QString messge);

    void createSuccessEvent();
    void createErrorEvent(QString message);

    void departmentJsonChanged();
    void locationJsonChanged();
    void typeJsonChanged();
    void typeIdChanged();
    void allowConflictChanged();
    void isEditModeChanged();
    void eventStartChanged();
    void eventEndChanged();
    void registerStartChanged();
    void registerEndChanged();
private:
    EventoEditController() = default;
public:
    void update(const DTO_Evento& event);

    void onLoadEditFinished() {
        emit loadEditSuccessEvent();
    }
    void onLoadEditFailure(const QString& msg) {
        emit loadEditErrorEvent(msg);
    }

    static EventoEditController *getInstance();
    static EventoEditController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // EVENTO_EDIT_CONTROLLER_H
