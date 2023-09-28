#ifndef TYPE_MANAGEMENT_H
#define TYPE_MANAGEMENT_H

#include <QtQml>

class TypeManagementController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(TypeManagementController)
    QML_SINGLETON

public:
    Q_INVOKABLE QString loadAllType();
    Q_INVOKABLE void deleteType(const int typeId);
    Q_INVOKABLE void changeTypeName(int id, const QString name);
    Q_INVOKABLE void addType(const QString name);

signals:
    void loadAllTypeSuccess();
    void loadAllTypeError(const QString& message);

    void deleteTypeSuccess();
    void deleteTypeError(const QString& message);

    void changeTypeNameSuccess();
    void changeTypeNameError(const QString& message);

    void addTypeSuccess();
    void addTypeError(const QString& message);

public:
    TypeManagementController() = default;
    static TypeManagementController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
};

#endif // TYPE_MANAGEMENT_H
