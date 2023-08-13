#ifndef LATEST_EVENTO_MODEL_H
#define LATEST_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

class LatestEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    explicit LatestEventoModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // LATEST_EVENTO_MODEL_H
