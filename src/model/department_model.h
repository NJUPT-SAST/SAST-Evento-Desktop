#ifndef DEPARTMENT_MODEL_H
#define DEPARTMENT_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "types.h"

class DepartmentModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(DepartmentModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Subscribed,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<Department>&& model);

private:
    DepartmentModel() = default;

    std::vector<Department> m_data;

public:
    static DepartmentModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static DepartmentModel* getInstance();
};

#endif // DEPARTMENT_MODEL_H
