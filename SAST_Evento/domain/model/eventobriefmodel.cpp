#include "eventobriefmodel.h"
#include "src/domain/eventobrief.h"

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

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::State:
        return static_cast<int>(
            element.getCheckState());
    case Role::Title:
        return element.getTitle();
    case Role::Date:
        return element.getDate();
    case Role::Location:
        return element.getLocation();
    case Role::Url:
        return element.getImage();
    case Role::Checked:
        return static_cast<int>(
            element.getCheckState());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> EventoBriefModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[State] = "state";
    roles[Title] = "title";
    roles[Date] = "date";
    roles[Location] = "location";
    roles[Url] = "url";
    roles[Checked] = "checked";
    return roles;
}

void EventoBriefModel::resetModel(const std::map<int, EventoBrief>& model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

void EventoBriefModel::append(const int id, const EventoBrief& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.insert(std::make_pair(id, item));
    endInsertRows();
}

void EventoBriefModel::removeByEventoID(const int id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = m_data.find(id);
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin(), iter);
    beginRemoveRows(QModelIndex(), idx, idx);
    m_data.erase(id);
    endRemoveRows();
}

void EventoBriefModel::changeItemByEventoID(const int id, const EventoBrief& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = m_data.find(id);
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin() ,iter);
    m_data.emplace(iter, item);
    emit dataChanged(index(idx), index(idx));
}
