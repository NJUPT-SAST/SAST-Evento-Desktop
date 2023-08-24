#ifndef EVENTO_BLOCK_MODEL_H
#define EVENTO_BLOCK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_block.h"

class EventoBlockModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EventoBlockModel)

public:
    enum Role
    {
        Id = Qt::UserRole + 1,
        Title,
        State,
        Data,
        Time,
        Location,
        Department,
        RowStart,
        RowEnd,
        ColunmStart,
        ColunmEnd,
        Finished,
        Editable,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventoBlock> model);

    EventoBlockModel(const EventoBlockModel &) = delete;
    EventoBlockModel &operator=(const EventoBlockModel &) = delete;

private:
    EventoBlockModel() = default;

    std::vector<EventoBlock> m_data;

    std::mutex m_mutex;

public:
    static EventoBlockModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    static EventoBlockModel *getInstance();
};

#endif // EVENTO_BLOCK_MODEL_H
