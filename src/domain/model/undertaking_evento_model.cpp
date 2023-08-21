#include "undertaking_evento_model.h"

int UndertakingEventoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant UndertakingEventoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::Time:
        return element.time;
    case Role::Location:
        return element.location;
    case Role::Department:
        return element.department;
    case Role::Url:
        return element.image;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> UndertakingEventoModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Time, "time");
        roles.insert(Location, "location");
        roles.insert(Department, "department");
        roles.insert(Url, "url");
    }
    return roles;
}

void UndertakingEventoModel::resetModel(const std::vector<UndertakingEvento> &model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

UndertakingEventoModel *UndertakingEventoModel::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

UndertakingEventoModel *UndertakingEventoModel::getInstance()
{
    static UndertakingEventoModel singleton;
    return &singleton;
}
