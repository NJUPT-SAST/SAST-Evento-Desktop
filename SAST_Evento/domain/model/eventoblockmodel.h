#ifndef EVENTOBLOCKMODEL_H
#define EVENTOBLOCKMODEL_H

#include <QAbstractListModel>
#include "domain/entity/eventoblock.h"

class EventoBlockModel : public QAbstractListModel
{
    Q_OBJECT

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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    EventoBlockModel(const EventoBlockModel&) = delete;
    EventoBlockModel& operator=(const EventoBlockModel&) = delete;

private:
    explicit EventoBlockModel(QObject *parent = nullptr);

    QList<EventoBlock> m_data;
};

inline EventoBlockModel *EventoBlockModel::getInstance(){
    static EventoBlockModel instance;
    return &instance;
}

#endif // EVENTOBLOCKMODEL_H
