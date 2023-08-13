#ifndef EVENTO_BLOCK_MODEL_H
#define EVENTO_BLOCK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_block.h"

class EventoBlockModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role{
        RowStart = Qt::UserRole + 1,
        RowEnd,
        ColumnStart,
        ColumnEnd,
        Date,
        Title,
        Description,
        Finished
    };

    static EventoBlockModel* getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {}

    EventoBlockModel(const EventoBlockModel&) = delete;
    EventoBlockModel& operator=(const EventoBlockModel&) = delete;

private:
    explicit EventoBlockModel(QObject *parent = nullptr);

    QList<EventoBlock> m_data;
};

#endif // EVENTO_BLOCK_MODEL_H
