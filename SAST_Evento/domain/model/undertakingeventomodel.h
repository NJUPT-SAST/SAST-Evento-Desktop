#ifndef UNDERTAKINGEVENTOMODEL_H
#define UNDERTAKINGEVENTOMODEL_H

#include <QAbstractListModel>

class UndertakingEventoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UndertakingEventoModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // UNDERTAKINGEVENTOMODEL_H
