#ifndef UNDERTAKING_EVENTO_MODEL_H
#define UNDERTAKING_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

class UndertakingEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    explicit UndertakingEventoModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // UNDERTAKING_EVENTO_MODEL_H
