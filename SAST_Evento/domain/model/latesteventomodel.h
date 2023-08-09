#ifndef LATESTEVENTOMODEL_H
#define LATESTEVENTOMODEL_H

#include <QAbstractListModel>

class LatestEventoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LatestEventoModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // LATESTEVENTOMODEL_H
