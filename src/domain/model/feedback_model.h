#ifndef FEEDBACK_MODEL_H
#define FEEDBACK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "feedback.h"

class FeedbackModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Score,
        Content,
        UserId,
        EventId,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Feedback>& model);

    static FeedbackModel* getInstance();

    FeedbackModel(const FeedbackModel&) = delete;
    FeedbackModel& operator=(const FeedbackModel&) = delete;

private:
    explicit FeedbackModel(QObject *parent = nullptr);

    std::vector<Feedback> m_data;

    std::mutex m_mutex;
};

#endif // FEEDBACK_MODEL_H
