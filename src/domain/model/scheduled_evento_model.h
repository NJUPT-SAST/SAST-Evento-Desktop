#ifndef SCHEDULED_EVENTO_MODEL_H
#define SCHEDULED_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

class ScheduledEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    explicit ScheduledEventoModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // SCHEDULED_EVENTO_MODEL_H
