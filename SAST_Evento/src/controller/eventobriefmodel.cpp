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

    switch (role) {
    case Role::State:
        return static_cast<int>(
            m_data[index.row()].getCheckState());
    case Role::Title:
        return m_data[index.row()].getTitle();
    case Role::Date:
        return m_data[index.row()].getDate();
    case Role::Location:
        return m_data[index.row()].getLocation();
    case Role::Url:
        return m_data[index.row()].getImage();
    case Role::Checked:
        return static_cast<int>(
            m_data[index.row()].getCheckState());
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

void EventoBriefModel::resetModel(const std::vector<EventoBrief>& model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

void EventoBriefModel::append(const EventoBrief& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.emplace_back(item);
    endInsertRows();
}

void EventoBriefModel::removeByEventoID(const QString& id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = std::find_if(m_data.begin(), m_data.end(),
                 [&id](const EventoBrief& ele) {
                     return ele.getEventoID() == id;
    });
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin() ,iter);
    beginRemoveRows(QModelIndex(), idx, idx);
    m_data.erase(iter);
    endRemoveRows();
}

void EventoBriefModel::changeItemByEventoID(const QString& id, const EventoBrief& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = std::find_if(m_data.begin(), m_data.end(),
                             [&id](const EventoBrief& ele) {
                                 return ele.getEventoID() == id;
                             });
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin() ,iter);
    m_data.emplace(iter, item);
    emit dataChanged(index(idx), index(idx));
}
