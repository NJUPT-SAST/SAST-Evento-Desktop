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
        State = Qt::DisplayPropertyRole + 1,
        Title,
        Date,
        Location,
        Url,
        Checked
    };

    static EventoBriefModel* getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<EventoBrief>& model);
    void append(const EventoBrief& item);
    void removeByEventoID(const QString& id);
    void changeItemByEventoID(const QString& id, const EventoBrief& item);

private:
    explicit EventoBriefModel(QObject *parent = nullptr);

    std::vector<EventoBrief> m_data;

    std::mutex m_mutex;
};

#endif // EVENTOBRIEFMODEL_H
