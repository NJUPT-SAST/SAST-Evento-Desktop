#include "evento_block_model.h"

/*
EventoBlockModel::FeedbackModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int EventoBlockModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant EventoBlockModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch(role) {
    case Role::Id:
        return element.id;
    case Role::Score:
        return element.score;
    case Role::Content:
        return element.content;
    case Role::UserId:
        return element.userId;
    case Role::EventId:
        return element.eventId;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> EventoBlockModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Score, "score");
        roles.insert(Content, "content");
        roles.insert(UserId, "userId");
        roles.insert(EventId, "eventId");
    }
    return roles;
}

void EventoBlockModel::resetModel(const std::vector<Feedback> &model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

EventoBlockModel *EventoBlockModel::getInstance()
{
    static EventoBlockModel instance;
    return &instance;
}
*/
