#ifndef EVENTO_BLOCK_MODEL_H
#define EVENTO_BLOCK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_block.h"

class EventoBlockModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EventoBlockModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Time,
        RowStart,
        RowEnd,
        ColumnStart,
        ColumnEnd,
        Editable,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventoBlock>&& model);

private:
    EventoBlockModel() = default;

    std::vector<EventoBlock> m_data;

public:
    static EventoBlockModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static EventoBlockModel* getInstance();
};

#endif // EVENTO_BLOCK_MODEL_H
