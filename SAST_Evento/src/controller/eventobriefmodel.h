#ifndef EVENTOBRIEFMODEL_H
#define EVENTOBRIEFMODEL_H

#include <QAbstractListModel>

class EventoBrief;

class EventoBriefModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        State = Qt::DisplayPropertyRole + 1,
        Title,
        Date,
        Location,
        Url,
        Checked
    };

    static EventoBriefModel* getInstance();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    explicit EventoBriefModel(QObject *parent = nullptr);

    QList<EventoBrief> m_data;
};

#endif // EVENTOBRIEFMODEL_H
