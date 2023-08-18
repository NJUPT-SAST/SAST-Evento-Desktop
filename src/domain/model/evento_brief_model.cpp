#include "evento_brief_model.h"

EventoBriefModel::EventoBriefModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int EventoBriefModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant EventoBriefModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    return QVariant();
}

QHash<int, QByteArray> EventoBriefModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Time, "time");
        roles.insert(State, "state");
        roles.insert(Description, "description");
        roles.insert(Url, "url");
    }
    return roles;
}

void EventoBriefModel::resetModel(const std::vector<EventoBrief>& model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

EventoBriefModel *EventoBriefModel::getInstance()
{
    static EventoBriefModel instance;
    return &instance;
}
