#ifndef CALENDARCONTROLLER_H
#define CALENDARCONTROLLER_H

#include <QtQml>

#include "types.h"

class CalendarController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(CalendarController)
    QML_SINGLETON

public:
    enum DepartmentEnum {
        SoftwareResearchAndDevelopmentDep,
        MultiMediaDep,
        ElectronicsDep,
    };
    Q_ENUM(DepartmentEnum)

public:
    Q_INVOKABLE void loadAllEventoInfo(QString date);
    Q_INVOKABLE void loadEventoInfo(EventoID eventId);
    Q_INVOKABLE void deleteEvento(EventoID eventId);
    Q_INVOKABLE void cancelEvento(EventoID eventId);
    Q_INVOKABLE void loadCheckCode(EventoID eventId);
    Q_INVOKABLE void generateLessonPic(QString date, DepartmentEnum dep);

signals:
    void loadAllEventoSuccessEvent();
    void loadAllEventoErrorEvent(QString message);

    void deleteSuccessEvent();
    void deleteErrorEvent(QString message);

    void cancelSuccessEvent();
    void cancelErrorEvent(QString message);

    void loadCheckCodeSuccessEvent(QString code);
    void loadCheckCodeErrorEvent(QString message);

    void loadPicSuccessEvent();
    void loadPicErrorEvent(QString message);

private:
    CalendarController();

public:
    void onLoadAllFinished() {
        emit loadAllEventoSuccessEvent();
    }
    void onLoadAllFailure(const QString& message) {
        emit loadAllEventoErrorEvent(message);
    }
    void onDeleteFinished() {
        emit deleteSuccessEvent();
    }
    void onDeleteFailure(const QString& message) {
        emit deleteErrorEvent(message);
    }
    void onCancelFinished() {
        emit cancelSuccessEvent();
    }
    void onCancelFailure(const QString& message) {
        emit cancelErrorEvent(message);
    }
    void onLoadCheckCodeFinished(const QString& code) {
        emit loadCheckCodeSuccessEvent(code);
    }
    void onLoadCheckCodeFailure(const QString& message) {
        emit loadCheckCodeErrorEvent(message);
    }
    void onLoadPicSuccess() {
        emit loadPicSuccessEvent();
    }
    void onLoadPicFailure(const QString& message) {
        emit loadPicErrorEvent(message);
    }

    static CalendarController* getInstance();
    static CalendarController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
};

#endif // CALENDARCONTROLLER_H
