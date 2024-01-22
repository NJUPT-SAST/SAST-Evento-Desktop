#ifndef FEEDBACKMODEL_H
#define FEEDBACKMODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "feedback.h"

class FeedbackModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(FeedbackModel)

public:
    enum Role {
        Score = Qt::UserRole + 1,
        Content,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<Feedback>&& model);

private:
    FeedbackModel() = default;

    std::vector<Feedback> m_data;

public:
    static FeedbackModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static FeedbackModel* getInstance();
};

#endif // FEEDBACKMODEL_H
