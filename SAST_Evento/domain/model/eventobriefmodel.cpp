#include "eventobriefmodel.h"
#include "domain/entity/eventobrief.h"
#include "infrastructure/util/util.hpp"

EventoBriefModel::EventoBriefModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

EventoBriefModel *EventoBriefModel::getInstance()
{
    static EventoBriefModel instance;
    return &instance;
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

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::State:
        return toUType(element.state);
    case Role::Description:
        return element.description;
    case Role::Time:
        return element.time;
    case Role::Url:
        return element.image.url;
    default:
        break;
    }

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
