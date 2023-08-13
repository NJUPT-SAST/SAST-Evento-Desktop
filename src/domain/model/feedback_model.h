#ifndef FEEDBACK_MODEL_H
#define FEEDBACK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

class FeedbackModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    explicit FeedbackModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // FEEDBACK_MODEL_H
