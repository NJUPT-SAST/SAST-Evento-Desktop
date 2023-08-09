#ifndef USERBRIEFMODEL_H
#define USERBRIEFMODEL_H

#include <QAbstractListModel>

class UserBriefModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UserBriefModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // USERBRIEFMODEL_H
