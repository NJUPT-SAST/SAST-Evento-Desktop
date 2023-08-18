#ifndef EVENTO_BLOCK_MODEL_H
#define EVENTO_BLOCK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>
#include <mutex>

#include "evento_block.h"

class EventoBlockModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role{
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

    void resetModel(const std::vector<EventoBlock>& model);

    static EventoBlockModel* getInstance();

    EventoBlockModel(const EventoBlockModel&) = delete;
    EventoBlockModel& operator=(const EventoBlockModel&) = delete;

private:
    explicit EventoBlockModel(QObject *parent = nullptr);

    std::vector<EventoBlock> m_data;

    std::mutex m_mutex;
};

#endif // EVENTO_BLOCK_MODEL_H
