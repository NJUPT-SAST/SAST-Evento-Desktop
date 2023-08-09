#ifndef FEEDBACKMODEL_H
#define FEEDBACKMODEL_H

#include <QAbstractListModel>

class FeedbackModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FeedbackModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // FEEDBACKMODEL_H
