#ifndef SCHEDULED_EVENTO_MODEL_H
#define SCHEDULED_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "src/domain/entity/schedule.h"

class ScheduledEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        State,
        Department,
        Location,
        Date,
        StartTime,
        EndTime,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Schedule>& model);

    static ScheduledEventoModel* getInstance();

    ScheduledEventoModel(const ScheduledEventoModel&) = delete;
    ScheduledEventoModel& operator=(const ScheduledEventoModel&) = delete;

private:
    explicit ScheduledEventoModel(QObject *parent = nullptr);

    std::vector<Schedule> m_data;

    std::mutex m_mutex;
};

#endif // SCHEDULED_EVENTO_MODEL_H
