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
    case Role::Time:
        return element.time;
    case Role::RowStart:
        return element.rowStart;
    case Role::RowEnd:
        return element.rowEnd;
    case Role::ColumnStart:
        return element.columnStart;
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
        roles.insert(Time, "time");
        roles.insert(RowStart, "rowStart");
        roles.insert(RowEnd, "rowEnd");
        roles.insert(ColumnStart, "columnStart");
        roles.insert(Editable, "editable");
    }
    return roles;
}

void EventoBlockModel::resetModel(std::vector<EventoBlock> model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

EventoBlockModel *EventoBlockModel::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

EventoBlockModel *EventoBlockModel::getInstance()
{
    static EventoBlockModel instance;
    return &instance;
}
