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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {}

    EventoBlockModel(const EventoBlockModel&) = delete;
    EventoBlockModel& operator=(const EventoBlockModel&) = delete;

private:
    EventoBlockModel() = default;

    QList<EventoBlock> m_data;
public:
    static EventoBlockModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    inline static EventoBlockModel *getInstance()
    {
        static EventoBlockModel singleton;
        return &singleton;
    }
};

#endif // EVENTO_BLOCK_MODEL_H
