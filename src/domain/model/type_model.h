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
        return m_data[index].id;
    }

    inline int getIndex(int id) {
        return std::distance(m_data.begin(),
                             std::find_if(m_data.begin(), m_data.end(),
                                          [=](const EventType& type) { return type.id == id; }));
    }

private:
    TypeModel() = default;

    std::vector<EventType> m_data;

public:
    static TypeModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static TypeModel* getInstance();
};

#endif // TYPEMODEL_H
