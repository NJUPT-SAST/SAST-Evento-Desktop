#ifndef SCHEDULED_EVENTO_MODEL_H
#define SCHEDULED_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "scheduled_evento.h"

class ScheduledEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(ScheduledEventoModel)

public:
    enum Role
    {
        Id = Qt::DisplayRole + 1,
        Title,
        State,
        Department,
        Location,
        Date,
        StartTime,
        EndTime,
        IsChecked,
        HasFeedback,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<Schedule> model);

    ScheduledEventoModel(const ScheduledEventoModel &) = delete;
    ScheduledEventoModel &operator=(const ScheduledEventoModel &) = delete;

private:
    ScheduledEventoModel() = default;

    std::vector<Schedule> m_data;

    std::mutex m_mutex;

public:
    static ScheduledEventoModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    static ScheduledEventoModel *getInstance();
};

#endif // SCHEDULED_EVENTO_MODEL_H
