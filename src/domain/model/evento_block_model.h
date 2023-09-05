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
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        Time,
        RowStart,
        RowEnd,
        ColumnStart,
        Editable,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventoBlock> model);

    EventoBlockModel(const EventoBlockModel &) = delete;
    EventoBlockModel &operator=(const EventoBlockModel &) = delete;

private:
    EventoBlockModel() //= default;
    {
        m_data.push_back({1, "title1", "10:00 - 11:00", 4, 5, 2, false});
        m_data.push_back({2, "title2", "14:00 - 16:00", 7, 9, 4, true});
        m_data.push_back({3, "title3", "14:30 - 15:30", 7.5, 8.5, 3, true});
        m_data.push_back({4, "title4", "19:00 - 20:00", 12, 13, 6, true});
    }

    std::vector<EventoBlock> m_data;

    std::mutex m_mutex;

public:
    static EventoBlockModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    static EventoBlockModel *getInstance();
};

#endif // EVENTO_BLOCK_MODEL_H
