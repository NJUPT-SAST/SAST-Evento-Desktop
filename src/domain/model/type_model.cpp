#include "type_model.h"

TypeModel *TypeModel::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

TypeModel *TypeModel::getInstance()
{
    static TypeModel singleton;
    return &singleton;
}

int TypeModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant TypeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto &element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Name:
        return element.name;
    case Role::AllowConflict:
        return element.allowConflict;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TypeModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Name, "name");
        roles.insert(AllowConflict, "allowConflict");
    }
    return roles;
}

void TypeModel::resetModel(std::vector<EventType> model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}
