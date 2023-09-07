#ifndef LOCATION_MANAGEMENT_H
#define LOCATION_MANAGEMENT_H

#include <QtQml>

class LocationManagementController : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LocationManagementController)
    QML_SINGLETON

public:
    Q_INVOKABLE QString loadAllLocation();
    Q_INVOKABLE void deleteLocation(const int locationId);
    Q_INVOKABLE void changeLocationName(int id, const QString name);
    Q_INVOKABLE void addLocation(const QString name, const int parentId);

signals:
    void loadAllLocationSuccess();
    void loadAllLocationError(const QString &message);

    void deleteTLocationSuccess();
    void deleteLocationError(const QString &message);

    void changeLocationNameSuccess();
    void changeLocationNameError(const QString &message);

    void addLocationSuccess();
    void addLocationError(const QString &message);

public:
    LocationManagementController() = default;
    static LocationManagementController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // LOCATION_MANAGEMENT_H
