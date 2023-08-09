#ifndef PERMISSIONMODEL_H
#define PERMISSIONMODEL_H

#include <QAbstractListModel>

class PermissionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PermissionModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // PERMISSIONMODEL_H
