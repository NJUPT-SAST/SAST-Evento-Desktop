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

    return m_data.count();
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

bool EventoBriefModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags EventoBriefModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool EventoBriefModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool EventoBriefModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}
