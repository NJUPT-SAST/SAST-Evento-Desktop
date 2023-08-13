#ifndef EVENTO_BRIEF_MODEL_H
#define EVENTO_BRIEF_MODEL_H

#include <QAbstractListModel>
#include <QtQml>
#include <mutex>

#include "evento_brief.h"

class EventoBriefModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        State,
        Description,
        Time,
        Url,
    };

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

#endif // EVENTO_BRIEF_MODEL_H
