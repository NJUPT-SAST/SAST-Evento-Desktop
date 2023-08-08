#ifndef EVENTOBRIEFMODEL_H
#define EVENTOBRIEFMODEL_H

#include <QAbstractListModel>
#include <mutex>

class EventoBrief;

class EventoBriefModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        State,
        Description,
        Time,
        Url,
    };

    static EventoBriefModel* getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<EventoBrief>& model);

    EventoBriefModel(const EventoBriefModel&) = delete;
    EventoBriefModel& operator=(const EventoBriefModel) = delete;

private:
    explicit EventoBriefModel(QObject *parent = nullptr);

    std::vector<EventoBrief> m_data;

    std::mutex m_mutex;
};

#endif // EVENTOBRIEFMODEL_H
