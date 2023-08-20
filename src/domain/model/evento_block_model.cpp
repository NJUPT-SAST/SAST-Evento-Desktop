#include "evento_block_model.h"

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

    const auto &element = m_data.at(index.row());

    switch (role)
    {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::State:
        return (int)element.state;
    case Role::Data:
        return element.data;
    case Role::Time:
        return element.time;
    case Role::Location:
        return element.location;
    case Role::Department:
        return element.department;
    case Role::RowStart:
        return element.rowStart;
    case Role::RowEnd:
        return element.rowEnd;
    case Role::ColunmStart:
        return element.colunmStart;
    case Role::ColunmEnd:
        return element.colunmEnd;
    case Role::Finished:
        return element.finished;
    case Role::Editable:
        return element.editable;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> EventoBlockModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty())
    {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(State, "state");
        roles.insert(Data, "data");
        roles.insert(Time, "time");
        roles.insert(Location, "location");
        roles.insert(Department, "department");
        roles.insert(RowStart, "rowStart");
        roles.insert(RowEnd, "rowEnd");
        roles.insert(ColunmStart, "colunmStart");
        roles.insert(ColunmEnd, "colunmEnd");
        roles.insert(Finished, "finished");
        roles.insert(Editable, "editable");
    }
    return roles;
}

void EventoBlockModel::resetModel(const std::vector<EventoBlock> &model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}
