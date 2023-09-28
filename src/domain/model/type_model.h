#ifndef TYPEMODEL_H
#define TYPEMODEL_H

#include "types.h"
#include <QAbstractListModel>
#include <QtQml>

class TypeModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(TypeModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Name,
        AllowConflict,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventType>&& model);
    inline int getID(int index) {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        return m_data[index].id;
    }

private:
    explicit TypeModel() = default;

    std::vector<EventType> m_data;

    std::mutex m_mutex;

public:
    static TypeModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static TypeModel* getInstance();
};

#endif // TYPEMODEL_H
