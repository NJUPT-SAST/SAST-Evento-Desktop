#include "scheduled_evento_model.h"

int ScheduledEventoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant ScheduledEventoModel::data(const QModelIndex &index, int role) const
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
    case Role::Department:
        return element.department;
    case Role::Location:
        return element.location;
    case Role::Date:
        return element.date;
    case Role::StartTime:
        return element.startTime;
    case Role::EndTime:
        return element.endTime;
    case Role::IsChecked:
        return element.isChecked;
    case Role::IsFeedback:
        return element.isFeedback;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> ScheduledEventoModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty())
    {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(State, "state");
        roles.insert(Department, "department");
        roles.insert(Location, "location");
        roles.insert(Date, "date");
        roles.insert(StartTime, "startTime");
        roles.insert(EndTime, "endTime");
        roles.insert(IsChecked, "isChecked");
        roles.insert(IsFeedback, "isFeedback");
    }
    return roles;
}

void ScheduledEventoModel::resetModel(const std::vector<Schedule> &model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

ScheduledEventoModel *ScheduledEventoModel::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

ScheduledEventoModel *ScheduledEventoModel::getInstance()
{
    static ScheduledEventoModel singleton;
    return &singleton;
}
