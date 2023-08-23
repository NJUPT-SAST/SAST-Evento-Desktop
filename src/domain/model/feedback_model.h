#ifndef FEEDBACK_MODEL_H
#define FEEDBACK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "feedback.h"

class FeedbackModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(FeedbackModel)

public:
    enum Role
    {
        Id = Qt::DisplayRole + 1,
        Score,
        Content,
        EventId,
        IsFeedback,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Feedback> &model);

private:
    FeedbackModel() = default;

    std::vector<Feedback> m_data;

    std::mutex m_mutex;

public:
    static FeedbackModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    static FeedbackModel *getInstance();
};

#endif // FEEDBACK_MODEL_H
